package JavaContainerPackage;


public interface JavaContainer<T> {

    /**
     * Adds an element to the set.
     *
     * @param element the element to be added
     * @throws IllegalArgumentException if the element is already in the set
     */
    void add(T element);

    /**
     * Removes an element from the Container.
     *
     * @param element the element to be removed
     * @throws IllegalArgumentException if the element is not in the Container
     */
    void remove(T element);

    /**
     * Returns the number of elements in the Container.
     *
     * @return the number of elements in the Container.
     */
    int size();

    /**
     * Returns an iterator over the elements in the Container.
     *
     * @return an iterator over the elements in the Container
     */
    Iterator<T> getIterator();

    /**
     * Prints the string representation of the set.
     */
    void print();

}
