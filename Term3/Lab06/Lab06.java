import java.util.StringTokenizer;

class IllegalArgumentCountException extends Exception {
	public IllegalArgumentCountException(String s) {
		super(s);
	}
}

public class Lab06 {
	public static void main(String[] args) {
		try {
			if (args.length != 2)
				throw new IllegalArgumentCountException("Provide only one string argument");	
		
	        StringTokenizer st = new StringTokenizer(args[1]);
		    StringBuilder newStr = new StringBuilder();
	        while (st.hasMoreTokens()) {
	            String s = st.nextToken();
	            if (s.length() > 1) {
	                newStr.append(s);
	                if (st.hasMoreTokens())
	                	newStr.append(" ");
	            }
	        }
	        System.out.println("Result: " + newStr);
		}
		catch (IllegalArgumentCountException err) {
			System.out.println(err.getMessage());
		}
	}
}
