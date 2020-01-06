package novemberizing.util;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 2. 7.
 */
@SuppressWarnings("unused")
public class Str {
    public static String From(BufferedReader reader){
        StringBuilder builder = new StringBuilder();
        String line;
        try {
            while((line = reader.readLine())!=null){
                builder.append(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return builder.toString();
    }

    public static String From(InputStream stream){
        return From(new BufferedReader(new InputStreamReader(stream)));
    }

    public static String Merge(String[] strings, String with ,int start){
        String ret = "";
        for(int i = start;i<strings.length;i++){
            ret += strings[i];
            ret += i+1<strings.length ? with : "";
        }
        return ret;
    }

    public static String Merge(String[] strings, String with ,int start, int end){
        String ret = "";
        for(int i = start;i<end && i<strings.length;i++){
            ret += strings[i];
            ret += (i+1<end && i+1<strings.length) ? with : "";
        }
        return ret;
    }
}
