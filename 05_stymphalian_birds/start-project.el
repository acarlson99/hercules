;;; start-project.el --- Start project of a specific type
;; Author: Alexander Carlson <alexandercarlson99@gmail.com>
;; Maintainer: Alexander Carlson <alexandercarlson99@gmail.com>
;; Created: 31 Mar 2019
;; Keywords: project
;; This file is not part of GNU Emacs.

;;; Commentary:
;; Hercules project for 42 Silicon Valley
;; The goal is to make a simple script to make starting projects easier/faster

;;; Code:

(defun clone-gitignore ()
  "Clone gitignore template."
  (if (y-or-n-p "Clone gitignore? ")
	  (progn
		(if (file-exists-p ".gitignore")
			(message ".gitignore file exists.  Skipping clone-gitignore")
		  (progn
			(message "cloning gitignore")
			(shell-command "git clone https://github.com/bombblob/gitignore_template.git gitignore_dir")
			(rename-file "gitignore_dir/.gitignore" "./.gitignore")
			(shell-command "rm -rf gitignore_dir"))))
	(message "skipping clone-gitignore")))

(defun clone-libft ()
  "Clone libft."
  (if (y-or-n-p "Clone libft? ")
	  (progn
		(if (file-exists-p "libft")
			(message "libft exists.  Skipping clone-libft")
		  (progn
			(message "cloning libft")
			(shell-command "git clone https://github.com/bombblob/libft.git libft")
			(shell-command "rm -rf libft/.git"))))
	(message "skipping clone-libft")))

(defun make-author ()
  "Create author file."
  (if (y-or-n-p "Create author file? ")
	  (progn
		(if (file-exists-p "author")
			(message "author file exists.  Skipping make-author")
		  (progn
			(message "creating author file")
			(append-to-file user-login-name nil "author")
			)))
	(message "skipping make-author")))

(defun git-init-project ()
  "Initialize git repo and maybe push to master."
  )

(defun start-project-c ()
  "Start a c project."
  (message "Starting c project")
  (make-author)
  (clone-gitignore)
  (clone-libft)
  (make-directory "src")
  (make-directory "inc")
  (with-temp-file "Makefile"
	(insert ""))
  )

(defun start-project (project-type)
  "Clone gitignore, libft(?), first push(?)\
and start project of type PROJECT-TYPE."
  (interactive "sWhat type of project? ")
  (cond
   ((string= project-type "c")
	(start-project-c))
   ((string= project-type "c++")
	(start-project-c++))
   ((string= project-type "go")
	(start-project-go))
   ((= 1 1)
	(message "Invalid project type"))
   )
  )

(provide 'start-project)
;;; start-project.el ends here
