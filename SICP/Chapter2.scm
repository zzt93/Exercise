;2.1
(define (make-rat a b)
  (define (gcd a b)
    (if (= a 0)
	b
	(gcd (remainder b a) a)))
  (let ((g (if (< (* a b) 0) (- (gcd a b)) (gcd a b))))
    (cons (/ a g) (/ b g))))

(define (numer x) (car x))
(define (denom x) (cdr x))

(define (print-rat x)
  (newline)
  (display (numer x))
  (display "/")
  (display (denom x)))

(print-rat (make-rat 2 -4))


;2.2
(define (midpoint-segment segment)
  (make-point (/ (+ (x-point (start-segment segment))
		    (x-point (end-segment segment)))
		 2)
	      (/ (+ (y-point (start-segment segment))
		    (y-point (end-segment segment)))
		 2)))

(define (make-segment x1 y1 x2 y2)
  (cons (make-point x1 y1) (make-point x2 y2)))

(define (start-segment segment) (car segment))

(define (end-segment segment) (cdr segment))

(define (make-point x y) (cons x y))

(define (x-point point) (car point))

(define (y-point point) (cdr point))

(define (print-point p)
  (newline)
  (display "(")
  (display (x-point p))
  (display ",")
  (display (y-point p))
  (display ")"))

(print-point (midpoint-segment (make-segment 1 2 3 4)))
  

;2.3

(define (perimeter-rect rect)
  (* (+ (width-rect rect) (height-rect rect)) 2))

(define (area-rect rect)
  (* (width-rect rect) (height-rect rect)))

(define (make-rect point1 point2)
  (cons point1 point2))

(define (abs n)
  (if (< n 0)
      (- n)
      n))
(define (width-rect rect)
  (abs (- (x-point (car rect)) (x-point (cdr rect)))))

(define (height-rect rect)
  (abs (- (y-point (car rect)) (y-point (cdr rect)))))


(define (make-point x y) (cons x y))

(define (x-point point) (car point))

(define (y-point point) (cdr point))

(define r (make-rect (make-point 0 0) (make-point 3 3)))

(perimeter-rect r)
(area-rect r)


;test

(define (cons x y)
  (define (dispatch m)
    (cond ((= m 0) x)
	  ((= m 1) y)
	  (else (error "!!!!" m))))
  dispatch)

(define (car z) (z 0))
(define (cdr z) (z 1))

(cons 1 2)


;2.4

(define (cons x y)
  (lambda (m) (m x y)))

(define (cdr z)
  (z (lambda (p q) q)))

(cdr (cons 1 2))

;2.5

(define (expt x n)
  (define (square n) (* n n))
  (cond ((= n 0) 1)
	((= (remainder n 2) 0) (square (expt x (/ n 2))))
	(else (* x (square (expt x (/ (- n 1) 2)))))))

(define (cons x y)
  (* (expt 2 x) (expt 3 y)))

(define (car x)
  (if (not (= (remainder x 2) 0))
      0
      (+ 1 (car (/ x 2)))))

(define (cdr x)
  (if (not (= (remainder x 3) 0))
      0
      (+ 1 (cdr (/ x 3)))))

(car (cons 6 3))
(cdr (cons 6 4))
      

;2.7

(define (make-interval a b) (cons a b))

(define (upper-bound interval)
  (let ((a (car interval))
	(b (cdr interval)))
    (if (> a b) a b)))

(define (lower-bound interval)
  (let ((a (car interval))
	(b (cdr interval)))
    (if (< a b) a b)))
      

(define interval (make-interval 311 211))
(upper-bound interval)
(lower-bound interval)

;2.8
(define (sub-interval x y)
  (make-interval (- (lower-bound x) (upper-bound y))
		 (- (upper-bound x) (lower-bound y))))

;2.10

(define (div-interval x y)
      (mul-interval x
		    (make-interval (/ 1.0 (upper-bound y))
				   (/ 1.0 (lower-bound y)))))

;2.11

(define (add-interval x y)
  (make-interval (+ (lower-bound x) (lower-bound y))
		 (+ (upper-bound x) (upper-bound y))))

(define (mul-interval x y)
  (let ((p1 (* (lower-bound x) (lower-bound y)))
	(p2 (* (lower-bound x) (upper-bound y)))
	(p3 (* (upper-bound x) (lower-bound y)))
	(p4 (* (upper-bound x) (upper-bound y))))
    (make-interval (min p1 p2 p3 p4)
		   (max p1 p2 p3 p4))))


(define (par1 r1 r2)
  (div-interval (mul-interval r1 r2)
		(add-interval r1 r2)))

(define (par2 r1 r2)
  (let ((one (make-interval 1 1)))
    (div-interval one
		  (add-interval (div-interval one r1)
				(div-interval one r2)))))

(par1 (make-interval 1 2) (make-interval 1 2))
(par2 (make-interval 1 2) (make-interval 1 2))

(define r1 (make-interval 1 2))
(define r2 (make-interval 1 2))
(define one (make-interval 1 1))

(mul-interval r1 r2)
(add-interval r1 r2)

(add-interval (div-interval one r1)
(div-interval one r2))

;2.17

(define (last-pair list)
  (if (null? (cdr list))
      list
      (last-pair (cdr list))))

(last-pair (list 1 2 3 4 5 6))

;2.18

(define (reverse list)
  (define (length list)
    (if (null? list)
	0
	(+ 1 (length (cdr list)))))
  (define (list-ref list n)
    (if (= n 0)
	(car list)
	(list-ref (cdr list) (- n 1))))
  (define (do-reverse list length)
    (if (< length 0)
	'()
	(cons (list-ref list length) (do-reverse list (- length 1)))))
  (do-reverse list (- (length list) 1)))
  

(reverse (list 1 2 3 4 5))

;2.19
(define us-coins (list 10 25 5 1 50))
(define (cc amount coin-values)
  (cond ((= amount 0) 1)
	((or (< amount 0) (null? coin-values)) 0)
	(else
	 (+ (cc amount (cdr coin-values))
	    (cc (- amount (car coin-values)) coin-values)))))

(cc 100 us-coins)

;2.20
(define (same-parity a . rest)
  (define (check x)
    (= (remainder (+ x a) 2) 0))
  (define (same-parity-iter list)
    (cond ((null? list)
	   '())
	  ((check (car list))
	   (cons (car list) (same-parity-iter (cdr list))))
	  (else
	   (same-parity-iter (cdr list)))))
  (cons a (same-parity-iter rest)))

(same-parity 0 2 3 4 5 6 7 99 3 7 4 5 6)

;2.21
(define (square-list list)
  (if (null? list)
      '()
      (cons ((lambda (n) (* n n)) (car list)) (square-list (cdr list)))))

(square-list (list 1 2 3 4 5))

(define (map proc list)
  (if (null? list)
      '()
      (cons (proc (car list)) (map proc (cdr list)))))

(define (square-list-new list)
  (map (lambda (x) (* x x)) list))

(square-list-new (list 1 2 3 4 5))

;2.23
(define (for-each proc list)
  (if (not (null? list))
      ((lambda x (for-each proc (cdr list))) (proc (car list)))))

(for-each (lambda (x) (newline) (display x))
	  (list 58 33 45))
	
;count-leaves
(define (count-leaves tree)
  (cond ((null? tree) 0)
	((not (pair? tree)) 1)
	(else (+ (count-leaves (car tree))
		 (count-leaves (cdr tree))))))

(count-leaves (cons (cons (list 1 2)
			  (list 1 2 3))
		    (list 3 4 3)))

;2.25

(define r1 (list 1 3 (list 5 7) 9))
(define r2 (list (list 7)))
(define r3 (list 1 (list 2 (list 3 (list 4 (list 5 (list 6 7)))))))

(car (cdr (car (cdr (cdr r1)))))
(car (car r2))
(car (cdr (car (cdr (car (cdr (car (cdr (car (cdr (car (cdr r3))))))))))))


(cons 1 2)
(cons 1 (cons 2 '()))
(list 1 2 3)

;2.26

(define (append x y)
  (if (null? x)
      y
      (cons (car x) (append (cdr x) y))))

(list (list 1 2 3) (list 1 2 3))

;2.27

(define (deep-reverse x)
  (define (deep-reverse-iter x k)
    (if (null? x)
	k
	(deep-reverse-iter (cdr x) (cons
				    (if (pair? (car x))
					(deep-reverse (car x))
					(car x))
				    k))))
  (deep-reverse-iter x '()))

(deep-reverse (list (list 1 2) (list 3 4)))

;2.28
(define (append a b)
  (if (null? a)
      b
      (cons (car a) (append (cdr a) b))))

(define (fringe tree)
  (cond ((null? tree) '())
	((not (pair? tree)) (list tree))
	(else
	 (append (fringe (car tree)) (fringe (cdr tree))))))

(define x (list (list 1 2) (list 3 4)))
(fringe (list x x))

;2.29 a)
(define (make-mobile left right)
  (list left right))

(define (make-branch length structure)
  (list length structure))

(define (left-branch mobile)
  (car mobile))

(define (right-branch mobile)
  (car (cdr mobile)))

(define (branch-length branch)
  (car branch))

(define (branch-structure branch)
  (car (cdr branch)))


(define l (make-branch 1 2))
(define r (make-branch 2 2))
(define m (make-mobile l r))
(define l2 (make-branch 1 m))
(define r2 (make-branch 1 m))
(define m2 (make-mobile l2 r2))

(branch-length (left-branch m))
(branch-structure (right-branch m))

;2.29 b)

(define (total-weight mobile)
  (if (not (pair? (branch-structure mobile)))
      (branch-structure mobile)
      (+ (total-weight (left-branch mobile))
	 (total-weight (right-branch mobile)))))

(total-weight (make-mobile (make-mobile m m) m))

;2.29 c)

(define (balance-mobile mobile)
  (define (branch-weight branch)
    (let ((tmp (branch-structure branch)))
      (if (pair? tmp)
	  (total-weight tmp)
	  tmp)))
  (let ((l (left-branch mobile))
	(r (right-branch mobile)))
    (= (* (branch-length l) (branch-weight l ))
       (* (branch-length r) (branch-weight r)))))

(balance-mobile m2)



;2.29 d)

(define (make-mobile l r)
  (cons l r))
(define (make-branch length structure)
  (cons length structure))

(define (left-branch mobile)
  (car mobile))

(define (right-branch mobile)
  (cdr mobile))

(define (branch-length branch)
  (car branch))

(define (branch-structure branch)
  (cdr branch))
	

;reverse-2

(define (reverse items)
  (if (null? items)
       '()
      (cons (reverse (cdr items))
	    (list (car items)))))

(reverse (list 1 2 3 4 5))

;2.30

(define (square-tree-1 tree)
  (cond ((null? tree) '())
	((not (pair? tree))
	 (* tree tree))
	(else
	 (cons (square-tree-1 (car tree))
	       (square-tree-1 (cdr tree))))))

(square-tree-1 (list (list (list 1 2) 2 ) 3 4))

(define (map proc list)
  (if (null? list)
      '()
      (cons (proc (car list)) (map proc (cdr list)))))


(define (square-tree-2 tree)
  (map (lambda (x)
	 (cond ((null? x) '())
	       ((not (pair? x)) (* x x))
	       (else (square-tree-2 x))))
       tree))

(square-tree-2 (list (list (list 1 2) 2 ) 3 4))

;2.31
(define (tree-map proc tree)
  (cond ((null? tree) '())
	((not (pair? tree))
	 (proc tree))
	(else
	 (cons (tree-map proc (car tree))
	       (tree-map proc (cdr tree))))))

(tree-map (lambda (x) (* x x x)) (list (list (list 1 2) 2 ) 3 4))

;2.32
(define (append a b)
  (if (null? a)
      b
      (cons (car a) (append (cdr a) b))))

(define (map proc list)
  (if (null? list)
      '()
      (cons (proc (car list)) (map proc (cdr list)))))

(define (subsets s)
  (if (null? s)
      (list '())
      (let ((rest (subsets (cdr s))))
	(append rest (map (lambda (x) (cons (car s) x)) rest)))))

(subsets (list 1 2 3))

;2.33

(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
	  (accumulate op initial (cdr sequence)))))

(define (map p sequence)
  (accumulate (lambda (x y) (cons (p x) y)) '() sequence))

(map (lambda (x) (* x x x)) (list 1 2 3 4))

(define (append seq1 seq2)
  (accumulate cons seq2 seq1))

(append (list 1 2 3) (list 4 5 6))

(define (length sequence)
  (accumulate (lambda (x y) (+ 1 y)) 0 sequence))

(length (list 1 2 3 5))

;2.34
(define (horner-eval x coeff-seq)
  (accumulate (lambda (this-coeff higher-termes)
		(+ this-coeff (* x (horner-eval x (cdr coeff-seq)))))
	      0
	      coeff-seq))

(horner-eval 2 (list 1 3 0 5 0 1))

;2.35
(define (count-leaves t)
  (accumulate + 0 (map (lambda (x) (if (pair? x)
				       (count-leaves x)
				       1))
		       t)))

(count-leaves (list 1 2 (list 1 2) 3 4 (list 1 2 (list 1 2) 3)))

;2.36
(define (accumulate-n op init seqs)
  (if (null? (car seqs))
      '()
      (cons (accumulate op init (map (lambda (x) (car x)) seqs))
	    (accumulate-n op init (map (lambda (x) (cdr x)) seqs)))))

(accumulate-n * 1 (list (list 1 2 3) (list 4 5 6) (list 7 8 9)))

;2.38
(define (fold-left op initial sequence)
  (define (fold-left-iter result seq)
    (if (null? seq)
	result
	(fold-left-iter (op result (car seq)) (cdr seq))))
  (fold-left-iter initial sequence))

(fold-left / 1 (list 1 2 3))
(accumulate / 1 (list 1 2 3))
(fold-left list '() (list 1 2 3))
(accumulate list '() (list 1 2 3))
(fold-left + 1 (list 1 2 3))

;2.39
(define (reverse-1 seq)
  (fold-left (lambda (x y) (cons y x)) '() seq))

(reverse-1 (list 1 2 3 4))

(define (reverse-2 seq)
  (accumulate (lambda (x y) (append y (list x))) '() seq))

(reverse-2 (list 1 2 3 4))

;2.40
(define (map proc seq)
  (if (null? seq)
      '()
      (cons (proc (car seq))
	    (map proc (cdr seq)))))

(define (enumerate-interval a b)
  (if (> a b)
      '()
      (cons a (enumerate-interval (+ a 1) b))))

(define (accumulate op init seq)
  (if (null? seq)
      init
      (op (car seq)
	  (accumulate op init (cdr seq)))))

(define (append a b)
  (accumulate cons b a))

(define (unique-pairs n)
  (accumulate append '() 
	      (map (lambda (i)
		     (map (lambda (j) (list i j))
			  (enumerate-interval 1 (- i 1))))
		   (enumerate-interval 1 n))))

(unique-pairs 10)

;2.41
(define (generate-triples n)
  (accumulate append '()
	      (map (lambda (i)
		     (accumulate append '()
		     (map (lambda (j)
			    (map (lambda (k) (list i j k))
				 (enumerate-interval 1 (- j 1))))
			  (enumerate-interval 1 (- i 1)))))
		   (enumerate-interval 1 n))))

(define (check-triples x s)
  (= (+ (car x) (cadr x) (caddr x)) s))

(define (filter check seq)
  (accumulate (lambda (x y)
		(if (check)
		    (cons x y)
		    y))
	      '()
	      seq))


(define (make-triple n s)
  (filter (lambda (x) (check-triples x s))
	  (generate-triples n)))
      

(make-triple 20 11)

;2.53

(define (memq item x)
  (cond ((null? x) #f)
	((eq? item (car x)) x)
	(else (memq item (cdr x)))))

(list 'a 'b 'c)
(list (list 'george))
(cdr '((x1 x2) (y1 y2)))
(cadr '((x1 x2) (y1 y2)))
(pair? (car '(a short list)))
(pair? (cdr '(a short list)))
(memq 'red '((red shoes) (blue socks)))
(memq 'red '(red shoes blue socks))

;2.54

(define (equal? list1 list2)
  (cond ((and (null? list1) (null? list2))
	 #t)
	((and (pair? list1) (pair? list2))
	 (and (equal? (car list1) (car list2))
	      (equal? (cdr list1) (cdr list2))))
	((not (or (pair? list1) (pair? list2)))
	 (eq? list1 list2))
	(else
	 #f)))

(equal? '(a (b) c (d (e))) '(a (b) c (d (e))))

;2.56

(define (=number? a num) (and (number? a) (= a num)))
(define (oprand-number exp)
  (if (null? exp)
      0
      (+ 1 (oprand-number (cdr exp)))))

(define (variable? exp) (symbol? exp))
(define (same-variable? var1 var2)
  (and (variable? var1) (variable? var2) (eq? var1 var2)))

(define (sum? exp)
  (and (pair? exp) (eq? (car exp) '+)))
(define (make-sum a b)
  (cond ((=number? a 0) b)
	((=number? b 0) a)
	((and (number? a) (number? b)) (+ a b))
	(else (list '+ a b))))
(define (addend exp) (cadr exp))
(define (augend exp)
  (if (= (oprand-number exp) 3)
      (caddr exp)
      (cons '+ (cddr exp))))

(define (product? exp)
  (and (pair? exp) (eq? (car exp) '*)))
(define (make-product a b)
  (cond ((or (=number? a 0) (=number? b 0)) 0)
	((=number? a 1) b)
	((=number? b 1) a)
	((and (number? a) (number? b)) (* a b))
	(else (list '* a b))))
(define (multiplier exp) (cadr exp))
(define (multiplicand exp)
  (if (= (oprand-number exp) 3)
      (caddr exp)
      (cons '* (cddr exp))))
(define (^ a b)
  (if (= b 1)
      a
      (* a (^ a (- b 1)))))
(define (exponentiation? exp)
  (and (pair? exp) (eq? (car exp) '^)))
(define (base exp) (cadr exp))
(define (exponent exp) (caddr exp))
(define (make-exponentiation a b)
  (cond ((or (=number? a 1) (=number? a 0)) 1)
	((=number? b 0) 0)
	((=number? b 1) a)
	((and (number? a) (number? b)) (^ a b))
	(else (list '^ a b))))

(define (deriv exp var)
  (cond ((number? exp)
	 0)
	((variable? exp)
	 (if (same-variable? exp var) 1 0))
	((sum? exp)
	 (make-sum (deriv (addend exp) var)
		   (deriv (augend exp) var)))
	((product? exp)
	 (make-sum
	  (make-product (multiplier exp)
			(deriv (multiplicand exp) var))
	  (make-product (deriv (multiplier exp) var)
			(multiplicand exp))))
	((exponentiation? exp)
	 (let ((b (base exp))
	       (e (exponent exp)))
	   (make-product e
			 (make-product (make-exponentiation b (- e 1))
				       (deriv b var)))))
	(else
	 (error "unknown expression type -- DERIV" exp))))

(deriv '(+ x 3 (^ x 2) x) 'x)
(deriv '(* x y) 'x)
(deriv '(* (* x y) (+ x 3)) 'x)







  

	