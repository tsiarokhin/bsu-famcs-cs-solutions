import java.lang.Math;

class IllegalArgumentCountException extends Exception {
	public IllegalArgumentCountException(String s) {
		super(s);
	}
}

public class Lab05 {
	public static void main(String[] args) {
		double x = 0;
		double e = 0;
		try {
			if (args.length	!= 3)
				throw new IllegalArgumentCountException("2 arguments required: x and e, " + (args.length-1) + " provided");
			x = Double.parseDouble(args[1]);
			e = Double.parseDouble(args[2]);
		} catch (IllegalArgumentCountException err) {
			System.out.println(err.getMessage());
			return;
		}
		catch (NumberFormatException err) {
			System.out.println("Wrong number format: " + err.getMessage());
			return;
		}

		double sum = -x;
		double prev = -x;
		double cur = 0;
		for (int k = 2; ; k++) {
			cur = prev * (-1) * x * (k-1) / k;
			if (Math.abs(cur) >= e) {
				sum += cur;
				prev = cur;
			} else
				break;
		}
		System.out.println("Sum: " + sum);
		return;
	}
}
