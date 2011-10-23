;Exe 1.3
(define (sum-of-bigger-2 a b c)
  (cond ((>= a b c) (+ a b))
	((>= a c b) (+ a c))
	((>= b a c) (+ b a))
	((>= b c a) (+ b c))
	((>= c a b) (+ c a))
	((>= c b a) (+ c b))))

(sum-of-bigger-2 3 10000 3111)

;Exe 1.4
;运算符作为...
(define (a-plus-abs-b a b)
  ((if (< b 0) - +) a b))

;Exe 1.5
;判断应用序还是正则序
(define (p) (p))

(define (test x y)
  (if (= x 0) 0 y))

(test 0 (p))


;Example 1.1.7
(define (sqrt x)
  (define (sqrt-iter guess)
    (define (good-enough?)
      (define (abs x)
	(if (< x 0) (- x) x))
      (< (abs (- (* guess guess) x)) 0.00001))
    (define (improve-guess)
      (/ (+ (/ x guess) guess) 2)) 
    (if (good-enough?)
	guess
	(sqrt-iter (improve-guess))))
  (sqrt-iter 1))

(sqrt 9.0)


;Exe 1.6
(define (sqrt x)
  (define (new-if predicate then-clause else-clause)
    (cond (predicate then-clause)
	  (else else-clause)))
  (define (sqrt-iter guess)
    (define (good-enough?)
      (define (abs x)
	(if (< x 0) (- x) x))
      (< (abs (- (* guess guess) x)) 0.000001))
    (define (improve-guess)
      (/ (+ (/ x guess) guess) 2)) 
    (new-if (good-enough?)
	guess
	(sqrt-iter (improve-guess))))
  (sqrt-iter 1))

(sqrt 9.0)

;1.2.2

(define (fib n)
  (define (fib-iter a b count)
    (if (= count 0)
	b
	(fib-iter b (+ a b) (- count 1))))
  (fib-iter 0 1 n))

(fib 0)

;1.11
(define (f n)
  (if (< n 3)
      n
      (+ (f (- n 1))
	 (* (f (- n 2)) 2)
	 (* (f (- n 3)) 3))))

(define (f-fast n)
  (define (f-iter a b c n)
    (if (< n 3)
	c
	(f-iter b c
		(+ (* 3 a) (* 2 b) c)
		(- n 1))))
  (if (< n 3)
      n
      (f-iter 0 1 2 n)))
  
(f-fast 25)
(f 25)

;1.2.4
(define (fast-expt b n)
  (define (square n)
    (* n n))
  (cond ((= n 0) 1)
	((= (remainder n 2) 0) (square (fast-expt b (/ n 2))))
	(else (* b (fast-expt b (- n 1))))))

(fast-expt 2 10)

;1.16
(define (fast-expt-new b n)
  (define (square n) (* n n))
  (define (even? n) (= (remainder n 2) 0))
  (define (fast-expt-iter a b n)
    (cond ((= n 0) a)
	  ((even? n) (fast-expt-iter a (square b) (/ n 2)))
	  (else (fast-expt-iter (* a b) (square b) (/ (- n 1) 2)))))
  (fast-expt-iter 1 b n))

(fast-expt-new 2 11)  

;1.17
(define (fast-expt-add b n)
  (define (* a b) (if (= b 0) 0 (+ a (* a (- b 1)))))
  (define (double n) (+ n n))
  (define (halve n) (/ n 2))
  (define (square n) (* n n))
  (define (even? n)
    (define (even-iter n a)
      (cond ((= n 0) #t)
	    ((= n 1) #f)
	    ((> n a) (even-iter n (double a))) 
	    ((< n a) (even-iter (- n (halve a)) 2))))
    (even-iter n 2))
  (define (fast-expt-iter a b n)
    (cond ((= n 0) a)
	  ((even? n) (fast-expt-iter a (square b) (/ n 2)))
	  (else (fast-expt-iter (* a b) (square b) (/ (- n 1) 2)))))
  (fast-expt-iter 1 b n))  

(fast-expt-add 3 6)

