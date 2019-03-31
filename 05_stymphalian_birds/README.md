# start-project.el

Small emacs package/lib/? to automate the creation of projects

## Installation

```bash
mv start-project.el ~/.emacs.d/lisp
```

Add the following to ~/.emacs.d/init.el

```scheme
(require 'start-project.el)
```

## Usage

From within emacs:

```
M-x mkdir project-name C-x C-f project-name M-x start-project RET rust RET
```
