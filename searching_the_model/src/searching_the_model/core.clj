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
  (count block))

(defn block-width [block]
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

;; This'll grow into a monster
(defn move-down! []
  (dosync 
   (alter current-block update-in [:location 1] inc)
   (let [current-block-x (-> @current-block :location (get 0))
         current-block-height (block-height @current-block)

         lowest-block-row (last (:block @current-block))
         
         lowest-row-y  (+ (-> @current-block :location (get 1))
                         current-block-height)
         lowest-row-xs  (filter #(pos? (get lowest-block-row %))
                                (range 0 (count lowest-block-row)))
         
         indexes-under-block (for [x lowest-row-xs]
                               [(inc lowest-row-y) (+ x current-block-x)])
         values-under-block (map #(get-in @world %) indexes-under-block)]
     ;;Do log

     (println "Lowest row-indexes of blocks: ")
     (pprint lowest-row-xs)
     
     (println "Values under block: ")
     (pprint values-under-block)

     (println "Indexes...")
     (println indexes-under-block)

     ;continue
     (when (or
            (some nil? values-under-block)
            (some pos? values-under-block))

       (alter world (fn [world]
                      (let [{[x y] :location
                             block :block} @current-block]
                        
                        (merge-2d-to-2d block world [x y]))))
       
       (put-block!)))
   (show-world)))

(defn move-horizontally [& {:keys [left?] :or {left? false}}]
  (swap! current-block update-in [:location 0] (if left? dec inc)))
  


