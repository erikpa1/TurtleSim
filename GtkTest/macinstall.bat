brew install pkgconf
brew install gtk4

pkg-config --modversion gtk4 Na otestovanie c ifunguje

export PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig:$PKG_CONFIG_PATH"