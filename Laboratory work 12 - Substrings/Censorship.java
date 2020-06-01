import java.math.BigInteger;
import java.util.*;

public class Main {
    static final int alph = 100;

    public static class Node {
        int next[];
        int p, ls, suflink;
        boolean term;

        Node(int np, int nls) {
            next = new int[alph];
            for (int i = 0; i < alph; i++)
                next[i] = -1;
            p = np;
            ls = nls;
            suflink = -1;
            term = false;
        }
    }

    static ArrayList <Node> trie = new ArrayList<>();

    static HashMap<Character, Integer> num = new HashMap<>();

    static void add(final String s) {
        int v = 0, c;
        for (int i = 0; i < s.length(); i++) {
            c = num.get(s.charAt(i));
            if (trie.get(v).next[c] == -1) {
                trie.add(new Node(v, c));
                trie.get(v).next[c] = (int)trie.size() - 1;
            }
            v = trie.get(v).next[c];
        }
        trie.get(v).term = true;
    }

    static int get_suflink(int v) {
        if (trie.get(v).suflink != -1)
            return trie.get(v).suflink;
        if (trie.get(v).p == 0)
            return 0;

        int cur = get_suflink(trie.get(v).p);
        while (cur > 0 && trie.get(cur).next[trie.get(v).ls] == -1)
            cur = get_suflink(cur);
        return (trie.get(cur).next[trie.get(v).ls] == -1 ? 0 : trie.get(cur).next[trie.get(v).ls]);
    }

    static boolean calced[];

    static boolean calc(int v) {
        if (calced[v])
            return trie.get(v).term;
        calced[v] = true;
        trie.get(v).term |= calc(trie.get(v).suflink);
        return trie.get(v).term;
    }

    static int go(int v, int c) {
        while (v > 0 && trie.get(v).next[c] == -1)
            v = trie.get(v).suflink;
        return (trie.get(v).next[c] == -1 ? 0 : trie.get(v).next[c]);
    }
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        trie.add(new Node(0, -1));

        int n, l, k, numeric = 0;
        k = in.nextInt();
        l = in.nextInt();
        n = in.nextInt();

        String cc = in.next();
        for (int i = 0; i < k; i++) {
            num.put(cc.charAt(i), numeric++);
        }

        String s;
        for (int i = 0; i < n; i++) {
            s = in.next();
            add(s);
        }

        n = trie.size();
        calced = new boolean[n];

        for (int i = 0; i < n; i++)
            trie.get(i).suflink = get_suflink(i);
        for (int i = 0; i < n; i++)
            trie.get(i).term = calc(i);

        int g[][] = new int[n][];
        for (int i = 0; i < n; i++) {
            g[i] = new int[k];
            for (int j = 0; j < k; j++)
                g[i][j] = -1;
        }

        for (int i = 0; i < n; i++) {
            if (trie.get(i).term)
                continue;
            for (int c = 0; c < k; c++) {
                int to = go(i, c);
                if (trie.get(to).term)
                    continue;
                g[i][c] = to;
            }
        }

        BigInteger dp[][] = new BigInteger[l + 1][];
        for (int i = 0; i <= l; i++) {
            dp[i] = new BigInteger[n];
            for (int j = 0; j < n; j++)
                dp[i][j] = new BigInteger("0");
        }
        dp[0][0] = new BigInteger("1");

        for (int i = 0; i < l; i++) {
            for (int v = 0; v < n; v++) {
                for (int j = 0; j < k; j++) {
                    int to = g[v][j];
                    if (to == -1)
                        continue;
                    dp[i + 1][to] = dp[i + 1][to].add(dp[i][v]);
                }
            }
        }

        BigInteger ans = new BigInteger("0");
        for (int i = 0; i < n; i++)
            ans = ans.add(dp[l][i]);
        System.out.print(ans);
    }
}
