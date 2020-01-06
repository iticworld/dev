package novemberizing.util;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 2. 9.
 */
public class Key {
    /** 64  */
    private static String __strings[] = {
            "AaBb0CcDd1EeFf2G",
            "gHh3IiJj4KkLl5Mm",
            "Nn6OoPp7QqRr8SsT",
            "t9UuVv+WwXx-YyZz"
    };

    public static String Encode(byte[] bytes){
        String gen = "";
        if(bytes!=null) {
            for (int i = 0; i < bytes.length; i++) {
                byte b = bytes[i];
                gen += __strings[i % 2].charAt((((b & 0xF0) >> 4) & 0x0F));
                gen += __strings[i % 2 + 1].charAt((b & 0x0F));
            }
        }
        return gen;
    }
    public static byte[] Decode(String key){
        if(key.length()%2==0 && key.length()>0) {
            byte[] ret = new byte[key.length()/2];
            for (int i = 0; i < key.length() / 2; i++) {
                int first = __strings[i % 2].indexOf(key.charAt(i * 2));
                int second = __strings[i % 2 + 1].indexOf(key.charAt(i * 2 + 1));
                if (first < 0 || second < 0) {
                    return null;
                }
                ret[i] = 0x00;
                ret[i] |= ((first<<4) | second);
            }
            return ret;
        }
        return null;
    }
}
