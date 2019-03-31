;;; package --- Summary
;;; Commentary:
;;; Code:

(defun clone-gitignore ()
  "Clone gitignore template."
  (if (file-exists-p ".gitignore")
	  (message ".gitignore file exists.  Skipping clone-gitignore")
	(progn
	  (message "cloning gitignore")
	  (shell-command "git clone https://github.com/bombblob/gitignore_template.git gitignore_dir")
	  (rename-file "gitignore_dir/.gitignore" "./.gitignore")
	  (shell-command "rm -rf gitignore_dir")
	  )))

(defun clone-libft ()
  "Clone libft."
  (if (file-exists-p "libft")
	  (message "libft exists.  Skipping clone-libft")
	(progn
	  (message "cloning libft")
	  (shell-command "git clone https://github.com/bombblob/libft.git libft")
	  (shell-command "rm -rf libft/.git")
	  )))

(defun make-author ()
  "Create author file."
  (append-to-file user-login-name nil "author")
  )

(provide 'start-project)
;;; start-project.el ends here
