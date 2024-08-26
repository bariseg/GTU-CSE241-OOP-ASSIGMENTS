package JavaContainerPackage;


/**
 * A generic vector implementation.
 *
 * @param <T> the type of elements in the Vector
 */

public class JavaVector<T> implements JavaContainer<T> {

    private Object[] elements;
    private int size;

    /**
     * Constructs an empty vector with an initial capacity of 1.
     */
    public JavaVector(){
        this.elements = new Object[1];
        this.size = 0;
    }

    /**
     * Returns the number of elements in the vector.
     *
     * @return the number of elements in the vector
     */
    @Override
    public int size() {
        return this.size;
    }

    /**
     * Prints the string representation of the vector.
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

        if (this.size == 0) return "empty vector";

        String result = "{ ";

        for (var e : this.elements){
            if (e != null) result += "(" + e.toString() + ") ";
        }

        result += "} size = "  + this.size() ;

        return result;
    }

    /**
     * Checks if this vector is equal to another object.
     *
     * @param other the object to compare with
     * @return true if the vectors are equal, false otherwise
     */
    @Override
    public boolean equals(Object other) {

        if (this == other) return true;
        if (other == null) return false;
        if (getClass() != other.getClass()) return false;

        JavaVector<T> otherVector = (JavaVector<T>) other;
        if (this.size() != otherVector.size()) return false;

        for (int i = 0 ; i < this.size ; i ++) {
            if (! this.elements[i].equals(otherVector.elements[i])) {
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
        if (this.size == elements.length){
            Object[] newElements = new Object[elements.length + 1];
            for (int i = 0; i < this.size; i++) newElements[i] = this.elements[i];
            this.elements = newElements ;
        }
        this.elements[this.size++] = element;
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
        }else throw new IllegalArgumentException( element + " is not in the vector");
    }

    /**
     * Returns an iterator over the elements in the set.
     *
     * @return an iterator over the elements in the set
     */
    @Override
    public Iterator<T> getIterator() {
        return new VectorIterator();
    }

    /**
     * Iterator implementation for the JavaVector class.
     */
    private class VectorIterator implements Iterator<T> {

        private int index;

        /**
         * Constructs a SetIterator with an initial index of 0.
         */
        public VectorIterator(){
            this.index = 0;
        }

        /**
         * Returns true if there are more elements in the vector.
         *
         * @return true if there are more elements, false otherwise
         */
        @Override
        public boolean hasNext() {
            return index < JavaVector.this.size();
        }

        /**
         * Returns the next element in the vector.
         *
         * @return the next element in the vector
         */
        @Override
        public T next() {
            return (T) JavaVector.this.elements[index++];
        }
    }


    private boolean includes(T element) {
        VectorIterator iterator = new VectorIterator();

        while (iterator.hasNext()) {
            if (iterator.next().equals(element)) {
                return true;
            }
        }
        return false;
    }



}
