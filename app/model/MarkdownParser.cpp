#include "MarkdownParser.h"

std::string& MarkdownParser::parseToHtml(const QString &markdownText)
{
    // Convert QString to std::string (UTF-8)
    std::string markdownUtf8 = markdownText.toUtf8().constData();

    // Parse the markdown text to a cmark node
    cmark_node *root = cmark_parse_document(markdownUtf8.c_str(), markdownUtf8.length(), CMARK_OPT_DEFAULT);

    // Render the cmark node to HTML
    char *htmlCStr = cmark_render_html(root, CMARK_OPT_DEFAULT, nullptr);
    static std::string htmlString;
    htmlString = std::string(htmlCStr);

    // Free allocated resources
    cmark_node_free(root);
    free(htmlCStr);

    return htmlString;
}
