# Markdown Editor - Qt-based Markdown Editor with WebView2 Rendering

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Qt](https://img.shields.io/badge/Qt-5.15%2B-green.svg)
![WebView2](https://img.shields.io/badge/WebView2-1.0%2B-orange.svg)
![vcpkg](https://img.shields.io/badge/vcpkg-enabled-blueviolet.svg)

A modern, feature-rich Markdown editor built with Qt framework, integrating CMark-gfm for parsing and WebView2 for high-quality rendering. Offers both WYSIWYG editing experience and real-time preview capabilities.

## ✨ Features

### 🎯 Core Functionality

- **Dual Editing Modes**: Rich text editing with Qt widgets + WebView2-based preview
- **Real-time Rendering**: Instant Markdown preview with WebView2
- **Syntax Highlighting**: Live syntax highlighting during editing
- **GitHub Flavored Markdown**: Full support for GFM through CMark-gfm

### 🖥️ User Interface

- **Modern Qt Interface**: Clean and intuitive user experience with ElaWidgetTools
- **Multiple Views**: Welcome screen, editor, and preview panels
- **Responsive Design**: Adaptable layout for different screen sizes
- **Theme Support**: Customizable appearance (planned)

### 📝 Editing Experience

- **Rich Text Editing**: Qt's powerful text editing capabilities
- **Live Syntax Highlighting**: Visual feedback for Markdown syntax
- **Partial Highlighting**: Selective highlighting during editing
- **Code Block Support**: Enhanced code editing experience

## 🏗️ Architecture

### Project Structure

```
src/
├── Model/
│   ├── DocumentModel.cpp/h          # Document data management
│   ├── FileManager.cpp/h            # File operations and persistence
│   ├── MarkdownParser.cpp/h         # CMark-gfm integration
│   ├── SyntaxHighlighter.cpp/h      # Text highlighting logic
│   └── tool.h                       # Utility functions
├── View/
│   ├── BaseView.cpp/h               # Base view class
│   ├── CoreView.cpp/h               # Main application view
│   ├── EditorView.cpp/h             # Markdown editor interface
│   ├── PreviewView.cpp/h            # WebView2 preview panel
│   ├── WelcomeView.cpp/h            # Welcome/start screen
│   └── CodePlainEditor.cpp/h        # Planned code editor
├── Presenter/
│   └── EditorPresenter.cpp/h        # MVP pattern presenter
├── MainWindow.cpp/h                 # Main application window
└── main.cpp                         # Application entry point
```

### Design Patterns

- **MVP (Model-View-Presenter)**: Clean separation of concerns
- **Modular Architecture**: Easily extensible components
- **Dependency Injection**: Loose coupling between components

## 🚀 Getting Started

### Prerequisites

- **Qt 5.15+** or **Qt 6.x** (develop base Qt 6.8.3)
- **vcpkg** for dependency management
- **C++17** compatible compiler (MSVC, GCC, or Clang)
- **ElaWidgetTools** (manual compilation required)

### Installation

#### Windows with vcpkg

1. **Install Qt manually** (to save compilation time):

   - Download Qt from [Qt Official Website](https://www.qt.io/download)
   - Use Qt Maintenance Tool or online installer
   - Select required modules: QtCore, QtGui, QtWidgets, QtWebEngine (if needed)

2. **Set up vcpkg**:

   ```bash
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   ```

3. **Install dependencies via vcpkg**:

   ```bash
   See vcpkg.json for more information
   ```

4. **Build ElaWidgetTools manually**:

   ```bash
   git clone https://github.com/ElaWidgetTools/ElaWidgetTools.git
   cd ElaWidgetTools
   # Follow ElaWidgetTools build instructions
   # Copy built libraries to 3rdparty/ElaWidgetTools in this project
   ```

5. **Clone and build the project**:

   ```bash
   git clone https://github.com/Yxz12-ye/md_editor.git
   cd md_editor
   mkdir build
   cd build
   
   # Configure with vcpkg toolchain
   cmake .. -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
   
   # Build
   cmake --build . --config Release
   ```

#### Linux (Planned)

```bash
# Similar setup with vcpkg and manual Qt installation
```

#### macOS (Planned)

```bash
# Similar setup with vcpkg and manual Qt installation
```

### Project Configuration

The project uses a hybrid dependency management approach:

- **vcpkg**: For CMark-gfm and WebView2 dependencies
- **Manual**: Qt framework (for faster setup)
- **3rdparty**: ElaWidgetTools custom components

### Directory Structure After Setup

```
md_editor/
├── src/                    # Source code
├── 3rdparty/
│   └── ElaWidgetTools/    # Manually built ElaWidgetTools
├── vcpkg_installed/       # vcpkg dependencies (auto-generated)
├── CMakeLists.txt
└── README.md
```

## 🛠️ Usage

### Basic Editing

1. Launch the application
2. Start typing Markdown in the editor
3. View real-time preview in the right panel
4. Use syntax highlighting for better editing experience

### File Operations

- **New File**: `Ctrl+N` or through Welcome screen
- **Open File**: `Ctrl+O` or drag-and-drop
- **Save File**: `Ctrl+S`
- **Export**: Multiple format support (planned)

### Advanced Features

- **Split View**: Edit and preview simultaneously
- **Theme Customization**: Adjust editor appearance
- **Keyboard Shortcuts**: Efficient workflow

## 🔧 Configuration

### vcpkg Integration

The project is configured to use vcpkg through CMake:

```cmake
# In CMakeLists.txt
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
```

### Build Configuration

```bash
# Example build commands
cmake -B build -DCMAKE_PREFIX_PATH="C:/Qt/6.5.0/msvc2019_64" -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg.cmake
cmake --build build --config Release
```

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guide](CONTRIBUTING.md) for details.

### Development Setup

1. Fork the repository
2. Set up dependencies as described above
3. Create a feature branch: `git checkout -b feature/amazing-feature`
4. Commit changes: `git commit -m 'Add amazing feature'`
5. Push to branch: `git push origin feature/amazing-feature`
6. Open a Pull Request

### Dependency Management

- Use vcpkg for new C/C++ dependencies
- Update vcpkg manifest if adding new packages
- Document any manual dependency requirements

## 📁 Project Status

### ✅ Implemented

- [x] Basic Markdown editing
- [x] WebView2 integration via vcpkg
- [x] Real-time preview
- [x] Syntax highlighting
- [x] File management
- [x] MVP architecture
- [x] vcpkg dependency management

### 🚧 In Progress

- [ ] Code block syntax highlighting
- [ ] Theme system
- [ ] Export functionality
- [ ] Plugin system

### 📋 Planned

- [ ] Multi-platform support (Linux, macOS)
- [ ] Plugin architecture
- [ ] Advanced export options (PDF, HTML)
- [ ] Collaboration features
- [ ] Version control integration

## 🐛 Troubleshooting

### Common Issues

**Qt not found:**

- Ensure Qt is installed manually and `CMAKE_PREFIX_PATH` is set correctly
- Check Qt version compatibility

**ElaWidgetTools missing:**

- Verify ElaWidgetTools is built and placed in `3rdparty/ElaWidgetTools`
- Check library paths in CMake configuration

**vcpkg dependencies:**

- Run `vcpkg integrate install` if having linking issues
- Ensure vcpkg toolchain file path is correct

**WebView2 not loading:**

- WebView2 Runtime should be automatically handled by vcpkg
- Check if WebView2 is installed system-wide

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **Qt Company** for the excellent framework
- **GitHub** for CMark-gfm
- **Microsoft** for WebView2 and vcpkg
- **ElaWidgetTools** for custom UI components

## 📞 Support

- **Issues**: [GitHub Issues](https://github.com/Yxz12-ye/md_editor/issues)

---

<div align="center">
Made with ❤️ using Qt, WebView2, and vcpkg
If you find this project useful, please give it a ⭐!
</div>


---

*Note: This project uses a hybrid dependency management approach for optimal development experience.*