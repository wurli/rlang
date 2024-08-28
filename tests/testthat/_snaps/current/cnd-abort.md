# withCallingHandlers() wrappers don't throw off trace capture on rethrow

    Code
      # `abort()` error
      print(err)
    Output
      <error/rlang_error>
      Error in `wch()`:
      ! High-level message
      Caused by error in `low3()`:
      ! Low-level message
      ---
      Backtrace:
           x
        1. +-testthat::expect_error(high1())
        2. | \-testthat:::expect_condition_matching(...)
        3. |   \-testthat:::quasi_capture(...)
        4. |     +-testthat (local) .capture(...)
        5. |     | \-base::withCallingHandlers(...)
        6. |     \-rlang::eval_bare(quo_get_expr(.quo), quo_get_env(.quo))
        7. \-rlang (local) high1()
        8.   \-rlang (local) high2()
        9.     \-rlang (local) high3()
       10.       +-rlang (local) wch(low1(), error = function(err) handler1(err))
       11.       | \-base::withCallingHandlers(expr, ...)
       12.       \-rlang (local) low1()
       13.         \-rlang (local) low2()
       14.           \-rlang (local) low3()
    Code
      summary(err)
    Output
      <error/rlang_error>
      Error in `wch()`:
      ! High-level message
      Caused by error in `low3()`:
      ! Low-level message
      ---
      Backtrace:
           x
        1. +-testthat::expect_error(high1())
        2. | \-testthat:::expect_condition_matching(...)
        3. |   \-testthat:::quasi_capture(...)
        4. |     +-testthat (local) .capture(...)
        5. |     | \-base::withCallingHandlers(...)
        6. |     \-rlang::eval_bare(quo_get_expr(.quo), quo_get_env(.quo))
        7. \-rlang (local) high1()
        8.   \-rlang (local) high2()
        9.     \-rlang (local) high3()
       10.       +-rlang (local) wch(low1(), error = function(err) handler1(err))
       11.       | \-base::withCallingHandlers(expr, ...)
       12.       \-rlang (local) low1()
       13.         \-rlang (local) low2()
       14.           \-rlang (local) low3()

---

    Code
      # C-level error
      print(err)
    Output
      <error/rlang_error>
      Error in `wch()`:
      ! High-level message
      Caused by error:
      ! Low-level message
      ---
      Backtrace:
           x
        1. +-testthat::expect_error(high1())
        2. | \-testthat:::expect_condition_matching(...)
        3. |   \-testthat:::quasi_capture(...)
        4. |     +-testthat (local) .capture(...)
        5. |     | \-base::withCallingHandlers(...)
        6. |     \-rlang::eval_bare(quo_get_expr(.quo), quo_get_env(.quo))
        7. \-rlang (local) high1()
        8.   \-rlang (local) high2()
        9.     \-rlang (local) high3()
       10.       +-rlang (local) wch(low1(), error = function(err) handler1(err))
       11.       | \-base::withCallingHandlers(expr, ...)
       12.       \-rlang (local) low1()
       13.         \-rlang (local) low2()
       14.           \-rlang (local) low3()
       15.             \-rlang (local) fail(NULL, "Low-level message")
    Code
      summary(err)
    Output
      <error/rlang_error>
      Error in `wch()`:
      ! High-level message
      Caused by error:
      ! Low-level message
      ---
      Backtrace:
           x
        1. +-testthat::expect_error(high1())
        2. | \-testthat:::expect_condition_matching(...)
        3. |   \-testthat:::quasi_capture(...)
        4. |     +-testthat (local) .capture(...)
        5. |     | \-base::withCallingHandlers(...)
        6. |     \-rlang::eval_bare(quo_get_expr(.quo), quo_get_env(.quo))
        7. \-rlang (local) high1()
        8.   \-rlang (local) high2()
        9.     \-rlang (local) high3()
       10.       +-rlang (local) wch(low1(), error = function(err) handler1(err))
       11.       | \-base::withCallingHandlers(expr, ...)
       12.       \-rlang (local) low1()
       13.         \-rlang (local) low2()
       14.           \-rlang (local) low3()
       15.             \-rlang (local) fail(NULL, "Low-level message")

# `parent = NA` signals a non-chained rethrow

    Code
      # Absent parent causes bad trace bottom
      hh <- (function() {
        withCallingHandlers(foo(), error = function(cnd) {
          abort(cnd_header(cnd))
        })
      })
      print(err(ff()))
    Output
      <error/rlang_error>
      Error in `h()`:
      ! bar
      ---
      Backtrace:
           x
        1. +-evaluate (local) `<fn>`()
        2. | +-base::withRestarts(...)
        3. | | \-base (local) withRestartList(expr, restarts)
        4. | |   +-base (local) withOneRestart(withRestartList(expr, restarts[-nr]), restarts[[nr]])
        5. | |   | \-base (local) doWithOneRestart(return(expr), restart)
        6. | |   \-base (local) withRestartList(expr, restarts[-nr])
        7. | |     +-base (local) withOneRestart(withRestartList(expr, restarts[-nr]), restarts[[nr]])
        8. | |     | \-base (local) doWithOneRestart(return(expr), restart)
        9. | |     \-base (local) withRestartList(expr, restarts[-nr])
       10. | |       \-base (local) withOneRestart(expr, restarts[[1L]])
       11. | |         \-base (local) doWithOneRestart(return(expr), restart)
       12. | +-evaluate:::with_handlers(...)
       13. | | +-base::eval(call)
       14. | | | \-base::eval(call)
       15. | | \-base::withCallingHandlers(...)
       16. | \-base::withVisible(do)
       17. +-base::print(err(ff()))
       18. +-rlang:::err(ff())
       19. | \-testthat::expect_error(...)
       20. |   \-testthat:::expect_condition_matching(...)
       21. |     \-testthat:::quasi_capture(...)
       22. |       +-testthat (local) .capture(...)
       23. |       | \-base::withCallingHandlers(...)
       24. |       \-rlang::eval_bare(quo_get_expr(.quo), quo_get_env(.quo))
       25. +-rlang (local) ff()
       26. | \-rlang (local) gg()
       27. |   \-rlang (local) hh()
       28. |     +-base::withCallingHandlers(...)
       29. |     \-rlang (local) foo()
       30. |       \-rlang (local) bar()
       31. |         \-rlang (local) baz()
       32. |           \-base::stop("bar")
       33. \-base::.handleSimpleError(`<fn>`, "bar", base::quote(baz()))
       34.   \-rlang (local) h(simpleError(msg, call))
    Code
      # Missing parent allows correct trace bottom
      hh <- (function() {
        withCallingHandlers(foo(), error = function(cnd) {
          abort(cnd_header(cnd), parent = NA)
        })
      })
      print(err(ff()))
    Output
      <error/rlang_error>
      Error in `hh()`:
      ! bar
      ---
      Backtrace:
           x
        1. +-evaluate (local) `<fn>`()
        2. | +-base::withRestarts(...)
        3. | | \-base (local) withRestartList(expr, restarts)
        4. | |   +-base (local) withOneRestart(withRestartList(expr, restarts[-nr]), restarts[[nr]])
        5. | |   | \-base (local) doWithOneRestart(return(expr), restart)
        6. | |   \-base (local) withRestartList(expr, restarts[-nr])
        7. | |     +-base (local) withOneRestart(withRestartList(expr, restarts[-nr]), restarts[[nr]])
        8. | |     | \-base (local) doWithOneRestart(return(expr), restart)
        9. | |     \-base (local) withRestartList(expr, restarts[-nr])
       10. | |       \-base (local) withOneRestart(expr, restarts[[1L]])
       11. | |         \-base (local) doWithOneRestart(return(expr), restart)
       12. | +-evaluate:::with_handlers(...)
       13. | | +-base::eval(call)
       14. | | | \-base::eval(call)
       15. | | \-base::withCallingHandlers(...)
       16. | \-base::withVisible(do)
       17. +-base::print(err(ff()))
       18. +-rlang:::err(ff())
       19. | \-testthat::expect_error(...)
       20. |   \-testthat:::expect_condition_matching(...)
       21. |     \-testthat:::quasi_capture(...)
       22. |       +-testthat (local) .capture(...)
       23. |       | \-base::withCallingHandlers(...)
       24. |       \-rlang::eval_bare(quo_get_expr(.quo), quo_get_env(.quo))
       25. \-rlang (local) ff()
       26.   \-rlang (local) gg()
       27.     \-rlang (local) hh()
       28.       +-base::withCallingHandlers(...)
       29.       \-rlang (local) foo()
       30.         \-rlang (local) bar()
       31.           \-rlang (local) baz()
       32.             \-base::stop("bar")
    Code
      # Wrapped handler
      handler1 <- (function(cnd, call = caller_env()) handler2(cnd, call))
      handler2 <- (function(cnd, call) abort(cnd_header(cnd), parent = NA, call = call))
      hh <- (function() {
        withCallingHandlers(foo(), error = function(cnd) handler1(cnd))
      })
      print(err(ff()))
    Output
      <error/rlang_error>
      Error in `hh()`:
      ! bar
      ---
      Backtrace:
           x
        1. +-evaluate (local) `<fn>`()
        2. | +-base::withRestarts(...)
        3. | | \-base (local) withRestartList(expr, restarts)
        4. | |   +-base (local) withOneRestart(withRestartList(expr, restarts[-nr]), restarts[[nr]])
        5. | |   | \-base (local) doWithOneRestart(return(expr), restart)
        6. | |   \-base (local) withRestartList(expr, restarts[-nr])
        7. | |     +-base (local) withOneRestart(withRestartList(expr, restarts[-nr]), restarts[[nr]])
        8. | |     | \-base (local) doWithOneRestart(return(expr), restart)
        9. | |     \-base (local) withRestartList(expr, restarts[-nr])
       10. | |       \-base (local) withOneRestart(expr, restarts[[1L]])
       11. | |         \-base (local) doWithOneRestart(return(expr), restart)
       12. | +-evaluate:::with_handlers(...)
       13. | | +-base::eval(call)
       14. | | | \-base::eval(call)
       15. | | \-base::withCallingHandlers(...)
       16. | \-base::withVisible(do)
       17. +-base::print(err(ff()))
       18. +-rlang:::err(ff())
       19. | \-testthat::expect_error(...)
       20. |   \-testthat:::expect_condition_matching(...)
       21. |     \-testthat:::quasi_capture(...)
       22. |       +-testthat (local) .capture(...)
       23. |       | \-base::withCallingHandlers(...)
       24. |       \-rlang::eval_bare(quo_get_expr(.quo), quo_get_env(.quo))
       25. \-rlang (local) ff()
       26.   \-rlang (local) gg()
       27.     \-rlang (local) hh()
       28.       +-base::withCallingHandlers(foo(), error = function(cnd) handler1(cnd))
       29.       \-rlang (local) foo()
       30.         \-rlang (local) bar()
       31.           \-rlang (local) baz()
       32.             \-base::stop("bar")
    Code
      # Wrapped handler, `try_fetch()`
      hh <- (function() {
        try_fetch(foo(), error = function(cnd) handler1(cnd))
      })
      print(err(ff()))
    Output
      <error/rlang_error>
      Error in `hh()`:
      ! bar
      ---
      Backtrace:
           x
        1. +-evaluate (local) `<fn>`()
        2. | +-base::withRestarts(...)
        3. | | \-base (local) withRestartList(expr, restarts)
        4. | |   +-base (local) withOneRestart(withRestartList(expr, restarts[-nr]), restarts[[nr]])
        5. | |   | \-base (local) doWithOneRestart(return(expr), restart)
        6. | |   \-base (local) withRestartList(expr, restarts[-nr])
        7. | |     +-base (local) withOneRestart(withRestartList(expr, restarts[-nr]), restarts[[nr]])
        8. | |     | \-base (local) doWithOneRestart(return(expr), restart)
        9. | |     \-base (local) withRestartList(expr, restarts[-nr])
       10. | |       \-base (local) withOneRestart(expr, restarts[[1L]])
       11. | |         \-base (local) doWithOneRestart(return(expr), restart)
       12. | +-evaluate:::with_handlers(...)
       13. | | +-base::eval(call)
       14. | | | \-base::eval(call)
       15. | | \-base::withCallingHandlers(...)
       16. | \-base::withVisible(do)
       17. +-base::print(err(ff()))
       18. +-rlang:::err(ff())
       19. | \-testthat::expect_error(...)
       20. |   \-testthat:::expect_condition_matching(...)
       21. |     \-testthat:::quasi_capture(...)
       22. |       +-testthat (local) .capture(...)
       23. |       | \-base::withCallingHandlers(...)
       24. |       \-rlang::eval_bare(quo_get_expr(.quo), quo_get_env(.quo))
       25. \-rlang (local) ff()
       26.   \-rlang (local) gg()
       27.     \-rlang (local) hh()
       28.       +-rlang::try_fetch(foo(), error = function(cnd) handler1(cnd))
       29.       | +-base::tryCatch(...)
       30.       | | \-base (local) tryCatchList(expr, classes, parentenv, handlers)
       31.       | |   \-base (local) tryCatchOne(expr, names, parentenv, handlers[[1L]])
       32.       | |     \-base (local) doTryCatch(return(expr), name, parentenv, handler)
       33.       | \-base::withCallingHandlers(...)
       34.       \-rlang (local) foo()
       35.         \-rlang (local) bar()
       36.           \-rlang (local) baz()
       37.             \-base::stop("bar")
    Code
      # Wrapped handler, incorrect `call`
      hh <- (function() {
        withCallingHandlers(foo(), error = handler1)
      })
      print(err(ff()))
    Output
      <error/rlang_error>
      Error in `.handleSimpleError()`:
      ! bar
      ---
      Backtrace:
           x
        1. +-evaluate (local) `<fn>`()
        2. | +-base::withRestarts(...)
        3. | | \-base (local) withRestartList(expr, restarts)
        4. | |   +-base (local) withOneRestart(withRestartList(expr, restarts[-nr]), restarts[[nr]])
        5. | |   | \-base (local) doWithOneRestart(return(expr), restart)
        6. | |   \-base (local) withRestartList(expr, restarts[-nr])
        7. | |     +-base (local) withOneRestart(withRestartList(expr, restarts[-nr]), restarts[[nr]])
        8. | |     | \-base (local) doWithOneRestart(return(expr), restart)
        9. | |     \-base (local) withRestartList(expr, restarts[-nr])
       10. | |       \-base (local) withOneRestart(expr, restarts[[1L]])
       11. | |         \-base (local) doWithOneRestart(return(expr), restart)
       12. | +-evaluate:::with_handlers(...)
       13. | | +-base::eval(call)
       14. | | | \-base::eval(call)
       15. | | \-base::withCallingHandlers(...)
       16. | \-base::withVisible(do)
       17. +-base::print(err(ff()))
       18. +-rlang:::err(ff())
       19. | \-testthat::expect_error(...)
       20. |   \-testthat:::expect_condition_matching(...)
       21. |     \-testthat:::quasi_capture(...)
       22. |       +-testthat (local) .capture(...)
       23. |       | \-base::withCallingHandlers(...)
       24. |       \-rlang::eval_bare(quo_get_expr(.quo), quo_get_env(.quo))
       25. \-rlang (local) ff()
       26.   \-rlang (local) gg()
       27.     \-rlang (local) hh()
       28.       +-base::withCallingHandlers(foo(), error = handler1)
       29.       \-rlang (local) foo()
       30.         \-rlang (local) bar()
       31.           \-rlang (local) baz()
       32.             \-base::stop("bar")

