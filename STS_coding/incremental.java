public class IncrementalSieve {
    // Standard Sieve to find initial primes
    static void simpleSieve(int limit, java.util.List<Integer> primes) {
        boolean[] isPrime = new boolean[limit + 1];
        for (int i = 2; i <= limit; i++) {
            isPrime[i] = true;
        }
        for (int p = 2; p * p <= limit; p++) {
            if (isPrime[p]) {
                for (int i = p * p; i <= limit; i += p) {
                    isPrime[i] = false;
                }
            }
        }
        for (int i = 2; i <= limit; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
        }
    }

    // Check if a number is prime using known primes
    static boolean isPrime(long n, java.util.List<Integer> primes) {
        for (int p : primes) {
            if (p * p > n) break;
            if (n % p == 0) return false;
        }
        return true;
    }

    // Incremental Sieve starting from n
    static void incrementalSieve(long start, int count) {
        int limit = (int) Math.sqrt(start + count);
        java.util.List<Integer> primes = new java.util.ArrayList<>();
        simpleSieve(limit, primes);

        for (long i = start; i < start + count; i++) {
            if (i < 2) continue;
            if (isPrime(i, primes)) {
                System.out.print(i + " ");
                if (i <= limit) primes.add((int) i);
            }
        }
    }

    public static void main(String[] args) {
        incrementalSieve(10, 20); // Find 20 numbers starting from 10
    }
}