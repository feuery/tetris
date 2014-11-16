(ns searching-the-model.core
  "For prototyping the state transitions of the game"
  (:require [clojure.pprint :refer [pprint]]
            [clojure.stacktrace :refer :all]))

;;; How to use?
;; Reset the world with (reset-world)
;; Move left-righ with move-horizontally
;; Move down with move-down
;; And check the world-state with show-world

(def W (/ 800 50))
(def H (/ 600 40))

(def world (ref (repeat H (-> W
                               (repeat 0)
                               vec))))

(def blocks
  [[[0 1]
    [1 1]
    [1 0]]

   [[1 0]
    [1 1]
    [0 1]]

   [[1]
    [1]
    [1]]

   [[1 1]
    [1 1]]

   [[1 0]
    [1 0]
    [1 1]]

   [[0 1]
    [0 1]
    [1 1]]])

(defn block-height [block]
  {:pre [(not (map? block))]}
  (count block))

(defn block-width [block]
  {:pre [(not (map? (first block)))]}
  (-> block first count))

(def current-block (ref nil))

(defn put-block! []
  (dosync
   (ref-set current-block {:location [(/ (count (first @world)) 2), 0]
                           :block (get blocks (rand-int (count blocks)))})))

(defn reset-world []
  (dosync
   (put-block!)
   (ref-set world (vec (repeat H (-> W
                                     (repeat 0)
                                     vec))))))
  

(defn merge-2d-to-2d
  "This'll be horrible, but easy to port to the C++"
  [block world [X Y]]
  (let [world (atom (vec
                     (map vec world)))] ;;Local state <3
    (dotimes [y (count block)]
      (let [row (get block y)]
        (dotimes [x (count row)]
          (swap! world assoc-in [(+ y Y) (+ X x)] (get-in block [y x])))))
    @world))
        

(defn show-world
  "Merges the current-block to the world"
  []
  (let [{[x y] :location
         block :block} @current-block]         
    (pprint (merge-2d-to-2d block @world [x y]))))


(defn transpose [seq-of-seqs]
  {:pre [(not (empty? seq-of-seqs))]}
  (apply mapv vector seq-of-seqs))

(defn indices [pred coll]
   (keep-indexed #(when (pred %2) %1) coll))

;; This'll grow into a monster
(defn move-down! []
  (dosync 
   (alter current-block update-in [:location 1] inc)
   (let [current-block-x (-> @current-block :location (get 0))
         current-block-y (-> @current-block :location (get 1))
         current-block-height (block-height (:block @current-block))

         vertical-block-rows (transpose (:block @current-block))
         
         xs (range 0 (if (= (block-width (:block @current-block)) 1)
                       (count vertical-block-rows)
                       (block-width (:block @current-block))))
         lowest-y-coords (->> xs
                              (map (fn [index]
                                     (-> pos?
                                         (indices (get vertical-block-rows index))
                                         last))))
         
         indexes-under-block (->> (map vector lowest-y-coords xs)
                                  (map (fn [[y x]] [(+ current-block-y (inc y))
                                                    (+ current-block-x x)]))
                                  vec)
                               
         values-under-block (map #(get-in @world %) indexes-under-block)]
     
     (when (or
            (some nil? values-under-block)
            (some pos? values-under-block))

       (alter world (fn [world]
                      (let [{[x y] :location
                             block :block} @current-block]
                        
                        (merge-2d-to-2d block world [x y]))))
       
       (put-block!)))
   (show-world)))

(defn can-we-move? [world current-block & {:keys [left?] :or {left? false}}]
  (let [{current-block :block
         [x y] :location} current-block
         left x
         right (+ x (dec (block-width current-block)))

         left-ys (map (partial + y) (indices #(= (first %) 1) current-block))
         right-ys (map (partial + y) (indices #(= (last %) 1) current-block))

         left-xs (repeat (count left-ys) (dec left))
         right-xs (repeat (count right-ys) (inc right))

         left-coordinates (map vector left-ys left-xs)
         right-coordinates (map vector right-ys right-xs)
         
         can-we-move-left? (->> left-coordinates
                                (map (fn [coord]
                                       (let [value (get-in world coord)]
                                         (= value 0))))
                                (reduce #(and %1 %2)))
         can-we-move-right? (->> right-coordinates
                                (map (fn [coord]
                                       (let [value (get-in world coord)]
                                         (= value 0))))
                                (reduce #(and %1 %2)))]
    ;; (println [can-we-move-left?
    ;;           can-we-move-right?])
    ;; (println "Indeksit: " right-coordinates)
    (if left?
      can-we-move-left?
      can-we-move-right?)))
    


    

(defn move-horizontally [& {:keys [left?] :or {left? false}}]
  (if (can-we-move? @world @current-block :left? left?)
    (dosync
     (alter current-block update-in [:location 0] (if left? dec inc))))
  (show-world))
  
(defn rotate [block]
  (->> block
       transpose 
       (map (comp vec reverse))
       vec))

(defn rotate-block! []
  (dosync
   (alter current-block update-in [:block] rotate))
  (show-world))

