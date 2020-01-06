package novemberizing;

public class bytes {
    public static byte[] clone(byte[] source, int n) {
        if(n < 0 || (source == null && n > 0)) {
            throw new RuntimeException("invalid parameter: n < 0 || (source == null && n > 0)");
        }
        if(source != null) {
            if(source.length < n) {
                System.out.println("source.length < n");
            }
            int length = (source.length < n ? source.length : n);
            byte[] destination = new byte[length];
            System.arraycopy(source, 0, destination, 0, length);
            return destination;
        }
        return null;
    }
}
