;;; package --- Summary
;;; Commentary:
;;; Code:
(defun clone-gitignore ()
  "Clone gitignore template."
  (magit-clone "https://github.com/bombblob/gitignore_template.git" "gitignore_dir")
  (rename-file "gitignore_dir/.gitignore" "./.gitignore")
  (delete-directory "gitignore_dir")
  )

;; this is broken :(

(defun clone-libft ()
  "Clone libft."
  (magit-clone "https://github.com/bombblob/libft.git")
  )

(defun make-author ()
  "Create author file."
  (append-to-file user-login-name nil "author")
  )

(provide 'manage-project)
;;; manage-project.el ends here
