import java.math.BigInteger;
import java.util.*;

public class Main {
    public static int m, mod;
    public static BigInteger n, two;

    public static int[][] mult(int[][] x, int[][] y) {
        int a = x.length, b = x[0].length, c = y[0].length;
        int[][] res = new int[a][];
        for (int i = 0; i < a; i++)
            res[i] = new int[c];

        for (int i = 0; i < a; i++) {
            for (int j = 0; j < c; j++) {
                for (int k = 0; k < b; k++)
                    res[i][j] = (res[i][j] + x[i][k] * y[k][j] % mod) % mod;
            }
        }
        return res;
    }

    public static int check(int a, int b) {
        for (int i = 1; i < m; i++) {
            int sum = 0;
            if (((1 << (i - 1)) & a) > 0)
                sum++;
            if (((1 << (i - 1)) & b) > 0)
                sum++;
            if (((1 << i) & a) > 0)
                sum++;
            if (((1 << i) & b) > 0)
                sum++;
            if (sum == 0 || sum == 4)
                return 0;
        }
        return 1;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        two = new BigInteger("2");
        n = in.nextBigInteger();
        n = n.subtract(BigInteger.ONE);
        m = in.nextInt();
        mod = in.nextInt();

        ArrayList<Integer> operations = new ArrayList<>();
        while (n.compareTo(BigInteger.ZERO) != 0) {
            if (n.mod(two).compareTo(BigInteger.ZERO) == 0) {
                operations.add(0);
                n = n.divide(two);
            }
            else {
                operations.add(1);
                n = n.subtract(BigInteger.ONE);
            }
        }

        int mat[][] = new int[(1 << m)][];
        for (int i = 0; i < (1 << m); i++)
            mat[i] = new int[(1 << m)];

        for (int a = 0; a < (1 << m); a++) {
            for (int b = 0; b < (1 << m); b++) {
                mat[a][b] = check(a, b);
            }
        }

        int dp[][] = new int[(1 << m)][];
        for (int i = 0; i < (1 << m); i++) {
            dp[i] = new int[1];
            dp[i][0] = 1;
        }

        int[][] res = new int[mat.length][];
        for (int i = 0; i < mat.length; i++)
            res[i] = new int[mat.length];
        for (int i = 0; i < mat.length; i++)
            res[i][i] = 1;

        for (int i = operations.size() - 1; i >= 0; i--) {
            if (operations.get(i) == 1)
                res = mult(res, mat);
            else
                res = mult(res, res);
        }
        res = mult(res, dp);

        int ans = 0;
        for (int i = 0; i < (1 << m); i++)
            ans = (ans + res[i][0]) % mod;
        System.out.print(ans);
    }
}
