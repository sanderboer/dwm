;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")
;;  removed (make-local-variable 'my-project-path)

;;((nil . ((eval . (progn BODY)))))
((nil . ( (eval . (progn
                      (message "project root finding ... ")
                      (setq sndr-project-root (sndr-dir-locals-dir))
                      (message (concat "project root is: " sndr-project-root))
                      (setq uname (replace-regexp-in-string "[ \n]+$" "" (shell-command-to-string "uname")))
                      (setq compilation-scroll-output t)
                      (setq compilation-scroll-output 'first-error)
                      (setq compile-command "make clean && make install")
                      (evil-leader/set-key
                          "m" 'compile
                          )
                      );; end progn
		);;end eval
	  );;end nil
      )
    )
