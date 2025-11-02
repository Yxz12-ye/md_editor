```
main.cpp
MainWindow

Model/DocumentModel
Model/FileManager
Model/MarkdownParser
Model/SyntaxHighlighter

Pressenter/EditorPresenter

View/BaseView
View/CoreView
View/EditorView
View/PreviewView
View/WelcomeView

```

`DocumentModel`用于处理活动页面的`QPlainTextEdit`里的`QTextDocument`

继承: 继承自`QObject`

私有成员

`QTextDocument* currentDocument`

`SyntaxHighlighter* highlighter`

`FileManager* fileManager`

`MarkdownParser* parser`

接口: 

`void updateDocument(QTextDocument* doc)` 设置活动页面的`QTextDocument`指针, 更新指针前断开先前的连接(如果有), 然后建立新连接, 完成后更新`SyntaxHighlighter`的指针

`void onSave(QTextDocument* doc)`控制`FileManager`进行保存

`QTextDocument* onOpen()`控制`FileManager`进行打开

槽函数

`void onTextUpdate()` 当文档内容变化后调用此函数, 函数会进行消抖动, 然后控制`SyntaxHighlighter`更新高亮

## TODO

 - [ ] 完成所有接口
 - [ ] 实现基础高亮
 - [ ] 实现代码块内代码高亮
 - [ ] 完成带行显示的`Widget`
 - [ ] 阶段性能优化
 - [ ] 实现Preview, 大致用`WebView`(毕竟我不想把软件做的特别大, 没`WebView`的支持以后再说)
 - [ ] 性能优化
 - [ ] 多平台支持