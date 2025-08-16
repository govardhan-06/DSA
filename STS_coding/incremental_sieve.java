import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the maximum value up to which you want prime numbers: ");
        int max = sc.nextInt();

        PrimeGenerator generator = new PrimeGenerator();

        System.out.println("Prime numbers up to " + max + " using Incremental Sieve:");
        while (true) {
            int prime = generator.nextPrime();
            if (prime > max) break;
            System.out.print(prime + " ");
        }
        sc.close();
    }
}

class PrimeGenerator {
    private int current = 2;
    private Map<Integer, List<Integer>> compositeMap = new HashMap<>();

    public int nextPrime() {
        while (true) {
            // Case 1: current not in map → it's prime
            if (!compositeMap.containsKey(current)) {
                compositeMap.put(current * current, new ArrayList<>(List.of(current)));
                return current++;
            } 
            // Case 2: current is composite → move its markers
            else {
                for (int prime : compositeMap.get(current)) {
                    int nextMultiple = current + prime;
                    compositeMap
                        .computeIfAbsent(nextMultiple, k -> new ArrayList<>())
                        .add(prime);
                }
                compositeMap.remove(current);
                current++;
            }
        }
    }
}
