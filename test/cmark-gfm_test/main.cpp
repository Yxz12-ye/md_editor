#include <cmark-gfm.h>
#include <cstdio>
#include <cstring>

#ifndef CMARK_OPT_GFM
#define CMARK_OPT_GFM 0
#endif

int main()
{
    // Initialize a simple markdown document
    const char *markdown = "# Hello, World!\nThis is a *markdown* document with **GFM** features.\n\n- Item 1\n- Item 2\n\n```cpp\n#include <iostream>\nint main() { std::cout << \"Hello, GFM!\" << std::endl; return 0; }\n```\n";

    // Parse the markdown document
    cmark_node *document = cmark_parse_document(markdown, strlen(markdown), CMARK_OPT_DEFAULT | CMARK_OPT_GFM);

    // Render the document to HTML
    char *html = cmark_render_html(document, CMARK_OPT_DEFAULT | CMARK_OPT_GFM, NULL);

    // Output the HTML
    printf("%s\n", html);

    // save the HTML to a file
    FILE *file = fopen("output.html", "w");
    if (file) {
        fprintf(file, "%s", html);
        fclose(file);
    }

    // Clean up
    cmark_node_free(document);
    cmark_get_default_mem_allocator()->free(html);

    return 0;
}