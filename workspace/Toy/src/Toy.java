import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.io.*;
import java.util.*;
import java.math.*;

public class Toy {
	static boolean LOCAL = System.getSecurityManager() == null;
	MyScanner input = new MyScanner(System.in);
	
	int[] m, k, ans;
	Segment T_T;
	
	int N;
	
	void run() {
		N = input.nextInt();
		T_T = new Segment(N);
		m = new int[N + 1];
		k = new int[N + 1];
		ans = new int[N + 1];
		for(int i = 1; i <= N; ++i) {
			k[i] = input.nextInt();
			m[i] = input.nextInt();
		}
		for(int i = N; i >= 1; --i) {
			//debug(k[i] + 1);
			int pos = T_T.query(k[i] + 1);
			//debug(pos);
			ans[pos] = m[i];
			T_T.modify(pos);
		}
		for(int i = 1; i <= N; ++i) {
			System.out.print(ans[i] + (i == N ? "\n" : " "));
		}
	}

	void debug(Object...os) {
		System.err.println(deepToString(os));
	}

	public static void main(String []args) {
		if(LOCAL) {
			try {
				System.setIn(new FileInputStream("in.txt"));
			}
			catch (Throwable e) {
				LOCAL = false;
			}
		}
		new Toy().run();
	}

}

class MyScanner {
	BufferedReader br;
	StringTokenizer st;

	MyScanner(InputStream in) {
		br = new BufferedReader(new InputStreamReader(in));
		eat("");
	}
	
	void eat(String s) {
		st = new StringTokenizer(s);
	}

	String nextLine() {
		try {
			return br.readLine();
		}
		catch(IOException e) {
			throw new IOError(e);
		}
	}

	boolean hasNext() {
		while(!st.hasMoreTokens()) {
			String s = nextLine();
			if(s == null) {
				return false;
			}
			eat(s);
		}
		return true;
	}

	String next() {
		hasNext();
		return st.nextToken();
	}

	int nextInt() {
		return Integer.parseInt(next());
	}

	long nextLong() {
		return Long.parseLong(next());
	}

	double nextDouble() {
		return Double.parseDouble(next());
	}

	BigInteger nextBigInteger() {
		return new BigInteger(next());
	}
}

class Segment {
	int []a;
	final int N;
	
	Segment(int n) {
		a = new int[(n + 1) * 2];
		N = n;
		build(1, N);
	}
	
	int getId(int l, int r) {
		if(l != r) {
			return l + r | 1;
		}
		else {
			return l + r;
		}
	}
	
	void build(int l, int r) {
		if(l == r) {
			a[getId(l, r)] = 1;
		}
		else {
			int m = (l + r) / 2;
			build(l, m);
			build(m + 1, r);
			a[getId(l, r)] = a[getId(l, m)] + a[getId(m + 1, r)];
		}
	}
	
	void modify(int l, int r, int x) {
		if(l == r) {
			a[getId(l, r)] = 0;
		}
		else {
			int m = (l + r) / 2;
			if(x <= m) {
				modify(l, m, x);
			}
			else {
				modify(m + 1, r, x);
			}
			a[getId(l, r)] = a[getId(l, m)] + a[getId(m + 1, r)];
		}
	}
	
	void modify(int x) {
		modify(1, N, x);
	}
	
	int query(int l, int r, int k) {
		if(l == r) {
			return l;
		}
		else {
			int m = (l + r) / 2;
			if(k <= a[getId(l, m)]) {
				return query(l, m, k);
			}
			else {
				return query(m + 1, r, k - a[getId(l, m)]);
			}
		}
	}
	
	int query(int k) {
		return query(1, N, k);
	}
}