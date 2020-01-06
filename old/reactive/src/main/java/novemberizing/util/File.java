package novemberizing.util;

import java.io.*;

/**
 *
 * @author novemberizing, me@novemberizing.net
 * @since 2017. 2. 5.
 */
@SuppressWarnings("unused")
public class File {
    private static final String Tag = "Util";

    public static void Set(String path, String str){
        BufferedWriter writer = null;
        try {
            writer = new BufferedWriter(new FileWriter(path));
            writer.write(str);
        } catch (IOException e) {
            Log.d(Tag, e.getMessage());
        } finally {
            if(writer!=null){
                try {
                    writer.close();
                } catch (IOException e) {
                    Log.d(Tag, e.getMessage());
                }
            }
        }
    }

    public static String Get(String path){
        String ret = "";
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new FileReader(path));
            String s;
            while ((s = reader.readLine()) != null) {
                ret += s;
                ret += "\n";
            }
        } catch (IOException e) {
            Log.d(Tag, e.getMessage());
        } finally {
            if(reader!=null){
                try {
                    reader.close();
                } catch (IOException e) {
                    Log.d(Tag, e.getMessage());
                }
            }
        }
        return ret;
    }
}
