package JavaContainerPackage;

/**
 * A generic set implementation.
 * @param <T> the type of elements in the set
 */
public class JavaSet<T> implements JavaContainer<T> {

    private Object[] elements;
    private int size;

    /**
     * Constructs an empty set with an initial capacity of 1.
     */
    JavaSet(){
        this.elements = new Object[1] ;
        this.size = 0;
    }

    /**
     * Returns the number of elements in the set.
     * @return the number of elements in the set
     */
    @Override
    public int size() {
        return this.size;
    }

    /**
     * Prints the string representation of the set.
     */
    @Override
    public void print() {
        System.out.println(this.toString());
    }

    /**
     * Returns a string representation of the set.
     *
     * @return a string representation of the set
     */
    @Override
    public String toString() {

        if (this.size == 0) return "empty set";

        String result = "{ ";

        for (var e : this.elements){
            if (e != null) result += "(" + e.toString() + ") ";
        }

        result += "} size = "  + this.size() ;

        return result;
    }

    /**
     * Checks if this set is equal to another object.
     *
     * @param other the object to compare with
     * @return true if the sets are equal, false otherwise
     */
    @Override
    public boolean equals(Object other) {

        if (this == other) return true;
        if (other == null) return false;
        if (getClass() != other.getClass()) return false;

        JavaSet<T> otherSet = (JavaSet<T>) other;
        if (this.size() != otherSet.size()) return false;

        for (int i = 0 ; i < this.size ; i ++) {
            if (!otherSet.includes((T) this.elements[i])) {
                return false;
            }
        }

        return true;
    }

    /**
     * Adds an element to the set.
     *
     * @param element the element to be added
     * @throws IllegalArgumentException if the element is already in the set
     */
    @Override
    public void add(T element) {
        if (! this.includes(element)){
            if (size == elements.length){
                Object[] newElements = new Object[elements.length + 1];
                for (int i = 0; i < this.size; i++) newElements[i] = this.elements[i];
                this.elements = newElements ;
            }
            this.elements[this.size++] = element;

        }else throw new IllegalArgumentException(element + " is already in the set");
    }

    /**
     * Removes an element from the set.
     *
     * @param element the element to be removed
     * @throws IllegalArgumentException if the element is not in the set
     */
    @Override
    public void remove(T element) {
        if (this.includes(element)){
            for (int i = 0; i < this.size; i++){
                if (this.elements[i].equals(element)) {
                    //shifts all elements left from element in index i to the last one
                    for (int j = i; j < this.size - 1; j++) elements[j] = elements[j + 1];

                    elements[this.size - 1] = null;
                    this.size--;
                    break;
                }
            }
        }else throw new IllegalArgumentException( element + " is not in the set");
    }

    /**
     * Returns an iterator over the elements in the set.
     *
     * @return an iterator over the elements in the set
     */
    @Override
    public Iterator<T> getIterator() {return new SetIterator(); }

    private boolean includes(T element) {
        SetIterator iterator = new SetIterator();
        while (iterator.hasNext()) {
            if (iterator.next().equals(element)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Iterator implementation for the JavaSet class.
     */
    private class SetIterator implements Iterator<T> {
        private int index ;

        /**
         * Constructs a SetIterator with an initial index of 0.
         */
        public SetIterator(){
            this.index = 0;
        }


        /**
         * Returns true if there are more elements in the set.
         *
         * @return true if there are more elements, false otherwise
         */
        @Override
        public boolean hasNext() {
            return index < JavaSet.this.size();
        }

        /**
         * Returns the next element in the set.
         *
         * @return the next element in the set
         */
        @Override
        public T next() {
            //add function handles type compatibility
            return (T) JavaSet.this.elements[index++];
        }
    } // class JavaSet.SetIterator

} //class JavaSet