import java.math.BigInteger;
import java.util.*;

public class Main {

    public static BigInteger sqrt(BigInteger x) {
        BigInteger l = BigInteger.ZERO, r = x;
        while (!l.equals(r)) {
            BigInteger mid = l.add(r).divide(BigInteger.valueOf(2));
            if (mid.equals(l)) {
                mid = mid.add(BigInteger.ONE);
            }
            if (mid.multiply(mid).compareTo(x) <= 0) {
                l = mid;
            } else {
                r = mid.subtract(BigInteger.ONE);
            }
        }
        return l;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        long b = in.nextLong();
        int k = in.nextInt();
        BigInteger n = in.nextBigInteger(16);

        if (k == 2) {
            BigInteger x = sqrt(n);
            while (!n.mod(x).equals(BigInteger.ZERO)) {
                x = x.subtract(BigInteger.ONE);
            }
            System.out.println(x.toString(16));
            System.out.println(n.divide(x).toString(16));
        } else {
            BigInteger x = sqrt(n).add(BigInteger.ONE);
            BigInteger d[] = new BigInteger[2];
            int pos = 0;
            while (pos < 2) {
                BigInteger g = x.multiply(x).subtract(n);
                BigInteger sg = sqrt(g);
                if (sg.multiply(sg).equals(g)) {
                    d[pos] = x.subtract(sg);
                    pos++;
                }
                x = x.add(BigInteger.ONE);
            }
            if (d[0].compareTo(d[1]) > 0) {
                BigInteger t = d[1];
                d[1] = d[0];
                d[0] = t;
            }
            BigInteger p1 = d[0].gcd(d[1]);
            BigInteger q1 = d[0].divide(p1);
            BigInteger p2, q2;
            if (d[1].mod(q1).equals(BigInteger.ZERO)) {
                p2 = d[1].divide(q1);
                q2 = n.divide(d[0]).divide(p2);
            } else {
                q2 = d[1].divide(p1);
                p2 = n.divide(d[0]).divide(q2);
            }
            if (p1.compareTo(q1) < 0) {
                System.out.println(p1.toString(16));
                System.out.println(p2.toString(16));
                System.out.println(q1.toString(16));
                System.out.println(q2.toString(16));
            } else {
                System.out.println(q1.toString(16));
                System.out.println(q2.toString(16));
                System.out.println(p1.toString(16));
                System.out.println(p2.toString(16));
            }
        }
    }
}
