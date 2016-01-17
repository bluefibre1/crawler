;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

((c++-mode . ((eval . (progn
                   (require 'projectile)
                   (setq flycheck-clang-include-path (delete-dups (append
                                                  flycheck-clang-include-path
                                                  (list (concat (projectile-project-root) "inc"))))))))))
