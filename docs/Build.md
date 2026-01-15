# Build & Docs

This page lists practical build instructions and common troubleshooting steps.

---

## Build Requirements

- C++ compiler (GCC / Clang / MSVC)
- raylib installed and linkable
- `make` (if using the Makefile)

---

## Build

From the project root:

```bash
make
```

Run the resulting executable (name depends on your Makefile), for example:

```bash
./game
```

---

## Generate Doxygen Documentation

### Requirements
- Doxygen installed
- (Recommended) Graphviz installed for diagrams

### Generate
```bash
make docs
```

Open:
- `docs/doxygen/html/index.html`

---

## Doxyfile Recommendations

Ensure these are enabled:

```ini
MARKDOWN_SUPPORT       = YES
USE_MDFILE_AS_MAINPAGE = README.md
INPUT                  = src include README.md docs
FILE_PATTERNS          = *.h *.hpp *.cpp *.md
RECURSIVE              = YES
GENERATE_HTML          = YES
```

---

## Troubleshooting

### Output directory error
If Doxygen complains about the output directory not existing, make sure the Makefile creates it:

```make
docs:
	@mkdir -p docs/doxygen
	doxygen Doxyfile
```

### Missing diagrams
If you want graphs/diagrams:
- Install Graphviz (`dot`)
- Set:
  - `HAVE_DOT = YES`

### Obsolete tags warning
If Doxygen warns about obsolete tags (like `CLASS_DIAGRAMS`), remove them and/or run:

```bash
doxygen -u Doxyfile
```
