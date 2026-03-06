#include "MarkdownParser.h"

#include <cstdlib>

namespace {
#ifdef CMARK_OPT_SOURCEPOS
constexpr int kCmarkRenderOptions = CMARK_OPT_DEFAULT | CMARK_OPT_SOURCEPOS;
#else
constexpr int kCmarkRenderOptions = CMARK_OPT_DEFAULT;
#endif

const char* kMarkdownCss = R"CSS(:root {
    color-scheme: light;
    --page-bg: #f6f8fb;
    --surface: #ffffff;
    --text: #1f2328;
    --muted: #57606a;
    --border: #d0d7de;
    --accent: #0969da;
    --code-bg: #f6f8fa;
    --quote: #656d76;
}

* {
    box-sizing: border-box;
}

html,
body {
    margin: 0;
    padding: 0;
}

body {
    font-family: "Segoe UI", "Noto Sans SC", "PingFang SC", "Microsoft YaHei", sans-serif;
    font-size: 16px;
    line-height: 1.7;
    color: var(--text);
    background: radial-gradient(1200px circle at top, #eef4ff 0%, var(--page-bg) 38%, #f5f7fb 100%);
    padding: 24px;
}

.markdown-body {
    max-width: 900px;
    margin: 0 auto;
    padding: 40px;
    background: var(--surface);
    border: 1px solid var(--border);
    border-radius: 14px;
    box-shadow: 0 14px 28px rgba(31, 35, 40, 0.08);
    overflow-wrap: anywhere;
}

.markdown-body:empty::before {
    content: "Start writing Markdown...";
    color: var(--muted);
}

.markdown-body h1,
.markdown-body h2,
.markdown-body h3,
.markdown-body h4,
.markdown-body h5,
.markdown-body h6 {
    margin: 1.4em 0 0.55em;
    line-height: 1.3;
    color: #151b23;
}

.markdown-body h1 {
    font-size: 2em;
    margin-top: 0;
    padding-bottom: 0.3em;
    border-bottom: 1px solid var(--border);
}

.markdown-body h2 {
    font-size: 1.5em;
    padding-bottom: 0.25em;
    border-bottom: 1px solid #eaeef2;
}

.markdown-body h3 {
    font-size: 1.25em;
}

.markdown-body p,
.markdown-body ul,
.markdown-body ol,
.markdown-body blockquote,
.markdown-body pre,
.markdown-body table,
.markdown-body hr {
    margin: 1em 0;
}

.markdown-body ul,
.markdown-body ol {
    padding-left: 1.6em;
}

.markdown-body li + li {
    margin-top: 0.3em;
}

.markdown-body blockquote {
    margin-left: 0;
    margin-right: 0;
    padding: 0.5em 1em;
    color: var(--quote);
    background: #f9fbff;
    border-left: 4px solid #9ec1f7;
    border-radius: 0 8px 8px 0;
}

.markdown-body a {
    color: var(--accent);
    text-decoration: underline;
    text-underline-offset: 2px;
}

.markdown-body a:hover {
    color: #0550ae;
}

.markdown-body code {
    font-family: "Cascadia Mono", "JetBrains Mono", "SFMono-Regular", Consolas, "Liberation Mono", monospace;
    font-size: 0.9em;
    padding: 0.16em 0.4em;
    border-radius: 6px;
    background: var(--code-bg);
}

.markdown-body pre {
    padding: 14px 16px;
    border-radius: 10px;
    background: #0f1722;
    overflow-x: auto;
}

.markdown-body pre code {
    padding: 0;
    color: #e6edf3;
    background: transparent;
    font-size: 0.9em;
    line-height: 1.6;
}

.markdown-body table {
    width: 100%;
    border-collapse: collapse;
    display: block;
    overflow-x: auto;
}

.markdown-body th,
.markdown-body td {
    padding: 10px 12px;
    border: 1px solid var(--border);
    text-align: left;
    white-space: nowrap;
}

.markdown-body th {
    background: #f3f6fa;
    font-weight: 600;
}

.markdown-body tr:nth-child(even) td {
    background: #fafcff;
}

.markdown-body hr {
    border: 0;
    border-top: 1px solid var(--border);
}

.markdown-body img {
    max-width: 100%;
    height: auto;
    border-radius: 8px;
    display: block;
}

@media (max-width: 900px) {
    body {
        padding: 12px;
    }

    .markdown-body {
        padding: 22px 16px;
        border-radius: 10px;
    }
}
)CSS";

bool IsBlankMarkdown(const std::string& markdownUtf8)
{
    return markdownUtf8.find_first_not_of(" \t\r\n") == std::string::npos;
}

std::string BuildHtmlDocument(const std::string& bodyHtml)
{
    std::string html;
    html.reserve(bodyHtml.size() + 6400);

    html += "<!doctype html>\n";
    html += "<html lang=\"en\">\n";
    html += "<head>\n";
    html += "  <meta charset=\"utf-8\">\n";
    html += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
    html += "  <style>\n";
    html += kMarkdownCss;
    html += "\n  </style>\n";
    html += "</head>\n";
    html += "<body>\n";
    html += "  <article class=\"markdown-body\">\n";
    html += bodyHtml;
    html += "\n  </article>\n";
    html += "</body>\n";
    html += "</html>\n";

    return html;
}

} // namespace

std::string MarkdownParser::parseToHtml(const QString& markdownText)
{
    const std::string markdownUtf8 = markdownText.toUtf8().toStdString();
    if (IsBlankMarkdown(markdownUtf8)) {
        return BuildHtmlDocument("");
    }

    cmark_node* root = cmark_parse_document(markdownUtf8.c_str(), markdownUtf8.length(), kCmarkRenderOptions);
    if (root == nullptr) {
        return BuildHtmlDocument("");
    }

    char* htmlCStr = cmark_render_html(root, kCmarkRenderOptions, nullptr);
    std::string renderedHtml;
    if (htmlCStr != nullptr) {
        renderedHtml = htmlCStr;
        free(htmlCStr);
    }

    cmark_node_free(root);
    return BuildHtmlDocument(renderedHtml);
}


