package novemberizing.util;

import java.util.Locale;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 2. 6.
 */
public class Hex {
    public static String To(byte[] bytes){
        String ret = "";
        for(int i=0;i<bytes.length;i++){
            ret += String.format(Locale.getDefault(), "%02x",bytes[i]);
        }
        return ret;
    }
}
