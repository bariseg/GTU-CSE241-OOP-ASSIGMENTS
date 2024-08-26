package JavaContainerPackage;


import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Driver {

    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {

        boolean goOn = true;

        do{
            String userInput = prompt();

            if (userInput.equals("OtoJavaSet")){
                OtoJavaSetTester();
            } else if (userInput.equals("OtoJavaVector")) {
                OtoJavaVectorTester();
            } else if (userInput.equals("ManualJavaSet")) {
                ManuelJavaSet();
            } else if (userInput.equals("ManualJavaVector")) {
                ManuelJavaVector();
            } else if (userInput.equals("exit")){
                goOn = false ;
                System.out.println("Exiting");
            }



        }while (goOn);

        scanner.close();
    }

    private static String prompt(){


        final String[] validCommands = {"OtoJavaSet", "OtoJavaVector","ManualJavaSet","ManualJavaVector","exit"};
        boolean invalidInput = false;

        String userInput = "";
        System.out.println("\n\n---------------Prompt--------------");
        System.out.println("Valid inputs (Enter one of them exactly the same):");
        for(var c : validCommands) System.out.println(c);

        do {

            try {

                invalidInput = true;

                System.out.print(">");
                userInput = scanner.nextLine();

                for (var c : validCommands){
                    if (c.equals(userInput)) {
                        invalidInput = false;
                        break;
                    }
                }
                if (invalidInput) throw new Exception(userInput);
            } catch (Exception e) {
                System.out.println("Invalid input : " + e.getMessage());
            }


        }while (invalidInput);


        return userInput;
    }

    private static void ManuelJavaSet(){

        boolean goOn = true;
        //Scanner scanner = new Scanner(System.in);
        int input = 0;

        JavaSet<Double> dblSet = new JavaSet<>();

        do {
            System.out.println("THIS IS A DOUBLE SET");
            System.out.println("1. add element to set");
            System.out.println("2. remove element from set");
            System.out.println("3. print set");
            System.out.println("4. get size of the set");
            System.out.println("5. write set to file");
            System.out.println("6. exit");
            System.out.print(">");

            input = scanner.nextInt();
            scanner.nextLine(); //cleaner
            try {
                switch (input){
                    case 1 :
                        System.out.print("Enter a double (Format depends on your devices local language notation 123.4 or 123,4 ): ");
                        dblSet.add(scanner.nextDouble());
                        break;
                    case 2 :
                        System.out.print("Enter a double to remove (Format depends on your devices local language notation 123.4 or 123,4 ) : ");
                        dblSet.remove(scanner.nextDouble());
                        break;
                    case 3 :
                        dblSet.print();
                        break;
                    case 4 :
                        System.out.println("Size : " + dblSet.size());
                        break;
                    case 5 :

                        File file = new File("saves.txt") ;
                        if (! file.exists()) file.createNewFile();

                        BufferedWriter writer = new BufferedWriter(new FileWriter(file,true));
                        writer.write("ManualDoubleSet : "+ dblSet.toString() + "\n");
                        writer.close();

                        break;
                    case 6 :
                        goOn = false;
                        break;

                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }


        }while (goOn);
        scanner.nextLine(); //cleaner
    }

    private static void ManuelJavaVector(){

        boolean goOn = true;
        //Scanner scanner = new Scanner(System.in);
        int input = 0;

        JavaVector<String> strVector = new JavaVector<>();

        do {
            System.out.println("THIS IS A STRING VECTOR");
            System.out.println("1. add element to vector");
            System.out.println("2. remove element from vector");
            System.out.println("3. print vector");
            System.out.println("4. get size of the vector");
            System.out.println("5. write vector to file");
            System.out.println("6. exit");
            System.out.print(">");

            input = scanner.nextInt();
            scanner.nextLine(); //cleaner
            try {
                switch (input){
                    case 1 :
                        System.out.print("Enter a string : ");
                        strVector.add(scanner.nextLine());
                        break;
                    case 2 :
                        System.out.print("Enter a string to remove : ");
                        strVector.remove(scanner.nextLine());
                        break;
                    case 3 :
                        strVector.print();
                        break;
                    case 4 :
                        System.out.println("Size : " + strVector.size());
                        break;
                    case 5 :

                        File file = new File("savesvector.txt") ;
                        if (! file.exists()) file.createNewFile();

                        BufferedWriter writer = new BufferedWriter(new FileWriter(file,true));
                        writer.write("ManualStringVector : "+ strVector.toString() + "\n");
                        writer.close();

                        break;
                    case 6 :
                        goOn = false;
                        break;

                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }


        }while (goOn);

    }






    private static void OtoJavaSetTester(){

        System.out.println("Some strSet Tests :");
        OtoStrSet();

        System.out.println("\n\nSome intSet tests : \n");
        OtoIntSet();

    }

    private static void OtoJavaVectorTester(){

        System.out.println("Some carVector tests :");

        OtoCarVector();

    }


    private static void OtoStrSet(){

        JavaSet<String> strSet = new JavaSet<>();
        System.out.println("Constructor :");
        strSet.print(); //this method also tests size() and toString() methods

        try{
            System.out.println("ismet and mustafa added to strSet :");
            strSet.add("ismet");
            strSet.add("mustafa");
            strSet.print();

            System.out.println("baris and eren added to strSet :");
            strSet.add("baris");
            strSet.add("eren");
            strSet.print();

        }catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }

        System.out.println("Invalid remove try Steve Jobs :");
        //invalid removing try
        try {
            strSet.remove("Steve Jobs");
        }catch (IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
        System.out.println("removing elements:");
        try {
            strSet.remove("baris");
            strSet.print();
            strSet.remove("eren");
            strSet.print();
            strSet.remove("mustafa");
            strSet.print();
            strSet.remove("ismet");
            strSet.print();

        }catch (IllegalArgumentException e){e.getMessage(); }

    }

    private static void OtoIntSet(){

        JavaSet<Integer> intSet = new JavaSet<>();
        System.out.println("Contructor :");
        intSet.print(); //this method also tests size() and toString() methods

        try{
            System.out.println("123 and 5345 added to intSet :");
            intSet.add(123);
            intSet.add(5345);
            intSet.print();

            System.out.println("1923 and 1919 added to intSet and 1919 is tried to add again:");
            intSet.add(1923);
            intSet.add(1919);
            intSet.print();

            intSet.add(1919);

        }catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }

        System.out.println("Invalid remove try 2002 :");
        //invalid removing try
        try {
            intSet.remove(2002);
        }catch (IllegalArgumentException e){
            System.out.println(e.getMessage());
        }

        System.out.println("removing elements:");
        try {
            intSet.remove(123);
            intSet.print();
            intSet.remove(1923);
            intSet.print();
            intSet.remove(1919);
            intSet.print();
            intSet.remove(5345);
            intSet.print();

        }catch (IllegalArgumentException e){e.getMessage(); }
    }

    private static void OtoCarVector(){



        JavaVector<Car> carVector = new JavaVector<>();
        Car anadol = new Car("Anadol", 1976);

        try {

            File file = new File("savesvector.txt") ;
            if (! file.exists()) file.createNewFile();

            BufferedWriter writer = new BufferedWriter(new FileWriter(file,true));
            writer.write("OtoCarVector\n");

            System.out.println("Adding some user defined Car class objects:");
            carVector.add(new Car("Mercedes C180", 2012));
            carVector.print();
            writer.write(carVector.toString() + "\n");
            carVector.add(new Car("Fiat Egea" , 2019));
            writer.write(carVector.toString() + "\n");
            carVector.print();

            carVector.add(anadol);
            carVector.add(anadol);
            carVector.print();
            writer.write(carVector.toString() + "\n");

            writer.close();

        } catch (Exception e) {
            System.out.println(e.getMessage());

        }


        try {
            System.out.println("Removing Anadol");
            carVector.remove(anadol);
            carVector.print();


            Car bmw = new Car("BMW 3.16i", 2005);
            System.out.println("Removing BMW,which is not in the vector");
            carVector.remove(bmw);


        }catch (Exception e) { System.out.println(e.getMessage());}




    }



    /**
     * Car class is a dummy class built for test purposes
     */
    private static class Car {

        private String name;
        private int model;

        public Car(String name, int model){
            this.name = name;
            this.model = model;
        }

        @Override
        public String toString() {
            return this.name + "," + this.model ;
        }

        @Override
        public boolean equals(Object obj) {
            return super.equals(obj);
        }
    }


}
