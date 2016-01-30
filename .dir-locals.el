;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

((c++-mode . ((eval . (progn
                        (require 'projectile)
                        (setq projectile-default-run-command "crawler")
                        (setq company-clang-arguments
                              (delete-dups (append
                                            company-clang-arguments
                                            (list (concat "-I" (projectile-project-root) "inc")))))
                        (setq flycheck-clang-include-path
                              (delete-dups (append
                                            flycheck-clang-include-path
                                            (list (concat (projectile-project-root) "inc"))))))))))
