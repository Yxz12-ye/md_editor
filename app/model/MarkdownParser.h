#pragma once

#include <cmark-gfm.h>
#include <string>
#include <QString>

class MarkdownParser
{
private:
    /* data */
public:
    MarkdownParser(/* args */){};
    ~MarkdownParser(){};

    std::string& parseToHtml(const QString &markdownText);
};

