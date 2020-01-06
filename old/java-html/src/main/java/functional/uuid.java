package functional;

import java.nio.charset.Charset;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.UUID;

/**
 * A UUID is 128 bits long, can guarantee uniqueness across space and time, and
 * requires no central registration process.
 *
 * @author      old.novemberizing <old.novemberizing@gmail.com>
 * @since       0.0.1
 */

@SuppressWarnings({"DanglingJavadoc", "WeakerAccess", "unused"})
public class uuid {
    public static class namespace {
        public static final UUID dns  = UUID.fromString("6ba7b810-9dad-11d1-80b4-00c04fd430c8");
        public static final UUID url  = UUID.fromString("6ba7b811-9dad-11d1-80b4-00c04fd430c8");
        public static final UUID oid  = UUID.fromString("6ba7b812-9dad-11d1-80b4-00c04fd430c8");
        public static final UUID x500 = UUID.fromString("6ba7b814-9dad-11d1-80b4-00c04fd430c8");

        private static UUID __default = null;

        /**
         * retrieve default namespace.
         *
         * - if {@link namespace#__default} is null, return a {@link namespace#url}
         *
         * @concurrency synchronized
         * @return      {@link UUID} default base uuid
         */
        private static synchronized UUID get(){ return __default!=null ? __default : url; }

        /**
         * set default base uuid
         *
         * @concurrency synchronized
         * @param v     {@link UUID} uuid
         */
        public static synchronized void set(UUID v){ __default = v; }
    }

    public static class to {
        /**
         * transform uuid to byte array
         *
         * @concurrency pure function
         * @param v     {@link UUID} uuid
         * @return      {@link byte[]} transformed byte array from uuid
         */
        public static byte[] bytes(UUID v){
            byte[] out = new byte[16];
            long msb = v.getMostSignificantBits();
            long lsb = v.getLeastSignificantBits();
            for(int i = 0; i < 8; i++){
                out[i] = (byte) ((msb >> ((7 - i) * 8)) & 0xFF);
            }
            for(int i = 8; i < 16; i++){
                out[i] = (byte) ((lsb >> ((15 - i) * 8)) & 0xFF);
            }
            return out;
        }
    }

    private static final Charset __utf8 = Charset.forName("utf8");
    private static Long __node = null;

    /**
     * set node information
     *
     * @concurrency -
     * @param v     {@link long} node
     */
    public static void node(long v){ __node = (v & 0x0000FFFFFFFFFFFFL); }

    /**
     * generate name uuid using byte array, custom base uuid, version and message digest
     *
     * - version code allow 0x00, 0x30 and 0x50
     *
     * @concurrency     pure function
     * @param bytes     {@link byte[]}        input value
     * @param namespace {@link UUID}          custom base uuid
     * @param version   {@link byte}          version code
     * @param md        {@link MessageDigest} message digest
     * @return {@link UUID} generated name based uuid
     */
    private static UUID from(byte[] bytes, UUID namespace, byte version, MessageDigest md){
        md.update(to.bytes(namespace));
        md.update(bytes);
        byte[] digest = md.digest();
        digest[6] &= 0x0F;
        digest[6] &= version;
        digest[8] &= 0x3F;
        digest[8] |= 0x80;
        return from(digest);
    }

    /**
     * transform byte array to uuid.
     *
     * - not use message digest, only transform bytes array to most significant bits and lest significant bits.
     *
     * @concurrency pure function
     * @param bytes {@link byte[]} byte array (must not null and array length is greater than or equal to 16)
     * @return {@link UUID} transformed uuid object
     */
    public static UUID from(byte[] bytes){
        if(bytes!=null  && bytes.length >= 16){
            long msb = 0;
            long lsb = 0;
            for (int i = 0; i < 8; i++) {
                msb = (msb << 8) | (bytes[i] & 0xFF);
            }
            for (int i = 8; i < 16; i++) {
                lsb = (lsb << 8) | (bytes[i] & 0xFF);
            }
            return new UUID(msb, lsb);
        }
        return null;
    }

    /**
     * transform uuid style string to uuid.
     *
     * @concurrency pure function
     * @param name {@link String} uuid style's string ("6ba7b810-9dad-11d1-80b4-00c04fd430c8")
     * @return {@link UUID} transformed uuid object
     */
    public static UUID from(String name) { return UUID.fromString(name); }

    /**
     * generate name based uuid using custom message digest and custom base uuid
     *
     * - version code is 0x00
     *
     * @concurrency pure function
     * @param name {@link String} input value
     * @param namespace {@link UUID} custom base uuid
     * @param md {@link MessageDigest} custom message digest
     * @return {@link UUID} generated uuid object (name based uuid and version code is 0x00)
     */
    public static UUID from(String name, UUID namespace, MessageDigest md){
        if(md != null){
            md.update(to.bytes(namespace));
            md.update(name.getBytes(__utf8));
            byte[] digest = md.digest();
            digest[6] &= 0x0F;
            digest[8] &= 0x3F;
            digest[8] |= 0x80;
            return from(digest);
        }
        return null;
    }

    /**
     * generate name based uuid using custom namespace and message digest
     *
     * - version code is 0x00
     *
     * @concurrency pure function
     * @param bytes {@link byte[]} input value
     * @param namespace {@link UUID} custom base uuid
     * @param md {@link MessageDigest} custom message digest
     * @return {@link UUID} generated uuid object (name based uuid and version code is 0x00)
     */
    public static UUID from(byte[] bytes, UUID namespace, MessageDigest md){
        if(md != null){
            md.update(to.bytes(namespace));
            md.update(bytes);
            byte[] digest = md.digest();
            digest[6] &= 0x0F;
            digest[8] &= 0x3F;
            digest[8] |= 0x80;
            return from(digest);
        }
        return null;
    }

    /**
     * generate name based uuid using custom message digest.
     *
     * - version code is 0x00
     * - base uuid using {@link namespace#__default} (if this value is null, using {@link namespace#url}
     *
     * @concurrency thread safety
     * @param name {@link String} input value
     * @param md {@link MessageDigest} custom message digest
     * @return {@link UUID} generated name based uuid (version code is 0x00)
     */
    public static UUID from(String name, MessageDigest md){ return from(name.getBytes(__utf8), md); }

    /**
     * generate name based uuid using custom message digest.
     *
     * - version code is 0x00
     * - base uuid using {@link namespace#__default} (if this value is null, using {@link namespace#url}
     *
     * @concurrency thread safety
     * @param bytes {@link byte[]} input value
     * @param md {@link MessageDigest} custom message digest
     * @return {@link UUID} generated name based uuid (version code is 0x00)
     */
    public static UUID from(byte[] bytes, MessageDigest md){
        if(md != null){
            md.update(to.bytes(namespace.get()));
            md.update(bytes);
            byte[] digest = md.digest();
            digest[6] &= 0x0F;
            digest[8] &= 0x3F;
            digest[8] |= 0x80;
            return from(digest);
        }
        return null;
    }

    /**
     * generated time based uuid (version 1) using current timestamp and system clock.
     *
     * - system clock using System.nanoTime()
     * - timestamp using System.currentTimeMillis()
     *
     * @concurrency not pure but thread safety
     * @return {@link UUID} time based uuid
     */
    public static UUID v1(){ return v1(System.currentTimeMillis(), System.nanoTime()); }

    /**
     * generate time based uuid using millisecond
     *
     * @concurrency not pure but thread safety
     * @param millisecond {@link long} millisecond
     * @return {@link UUID} generated time based uuid
     */
    public static UUID v1(long millisecond) { return v1(millisecond, System.nanoTime()); }

    /**
     * generate time based uuid using millisecond and system's clock.
     *
     * @concurrency pure function
     * @param millisecond {@link long} millisecond
     * @param nano {@link long} system's nano time
     * @return {@link UUID} generated time based uuid.
     */
    public static UUID v1(long millisecond, long nano){
        millisecond += 12219292800000L; /** gregorian adjust millisecond */
        millisecond *= 10000;
        long time = ((millisecond << 32) | ((millisecond & 0xFFFF00000000L) >> 16)) | (((millisecond >> 48) & 0x0FFF) | 0x1000);
        long clock = (nano << 48);
        long lsb = clock | __node;
        return new UUID(time, lsb);
    }

    /**
     * generate name based uuid using default base uuid (version 3)
     *
     * - if {@link namespace#__default} is null, use {@link namespace#url}
     * - version code is 0x30
     *
     * @concurrency not pure but thread safe
     * @param name {@link String} input value
     * @return {@link UUID} name based uuid (version 3)
     */
    public static UUID v3(String name){ return v3(name.getBytes(__utf8)); }

    /**
     * generate name based uuid using default base uuid (version 3)
     *
     * - if {@link namespace#__default} is null, use {@link namespace#url}
     * - version code is 0x30
     *
     * @concurrency not pure but thread safe
     * @param bytes {@link byte[]} input value
     * @return {@link UUID} name based uuid
     */
    public static UUID v3(byte[] bytes){ return UUID.nameUUIDFromBytes(bytes); }

    /**
     * generate name based uuid using custom base uuid (version 3)
     *
     * - version code is 0x30
     *
     * @concurrency pure function
     * @param name {@link String} input value
     * @param namespace {@link UUID} custom base uuid
     * @return {@link UUID} name based uuid version 3
     */
    public static UUID v3(String name, UUID namespace) { return v3(name.getBytes(__utf8), namespace); }

    /**
     * generate name based uuid using custom base uuid (version 3)
     *
     * - version code is 0x30
     * @param bytes {@link byte[]} input value
     * @param namespace {@link UUID} custom base uuid
     * @return {@link UUID} name based uuid version 3
     */
    public static UUID v3(byte[] bytes, UUID namespace){
        try {
            return from(bytes, namespace, (byte) 0x30, MessageDigest.getInstance("MD5"));
        } catch (NoSuchAlgorithmException e) {
            /** never throw any exception, if throw exception, system is critical state. */
        }
        return UUID.nameUUIDFromBytes(bytes);
    }

    /**
     * generate random uuid (version 4)
     *
     * @concurrency not pure and thread safe
     * @return {@link UUID} generated random uuid
     */
    public static UUID v4(){ return UUID.randomUUID(); }

    /**
     * generate name based uuid using default base uuid (version 5)
     *
     * - if {@link namespace#__default} is null, use {@link namespace#url}
     * - version code is 0x50
     *
     * @concurrency not pure but thread safe.
     * @param name {@link String} input value
     * @return {@link UUID} generate name base uuid (version 5)
     */
    public static UUID v5(String name){ return v5(name.getBytes(__utf8)); }

    /**
     * generate name based uuid using default base uuid (version 5)
     *
     * - if {@link namespace#__default} is null, use {@link namespace#url}
     * - version code is 0x50
     *
     * @concurrency not pure but thread safe.
     * @param bytes {@link byte[]} input value
     * @return {@link UUID} generate name base uuid (version 5)
     */
    public static UUID v5(byte[] bytes){ return v5(bytes, namespace.get()); }

    /**
     * generate name based uuid using custom base uuid (version 5)
     *
     * - version code is 0x50
     *
     * @concurrency pure function
     * @param name {@link String} input value
     * @param namespace {@link UUID} custom name base uuid
     * @return {@link UUID} generated name base uuid
     */
    public static UUID v5(String name, UUID namespace){ return v5(name.getBytes(__utf8), namespace); }

    /**
     * generate name based uuid using custom base uuid (version 5)
     *
     * - version code is 0x50
     *
     * @concurrency pure function
     * @param bytes {@link byte[]} input value
     * @param namespace {@link UUID} custom name base uuid
     * @return {@link UUID} generated name base uuid
     */
    public static UUID v5(byte[] bytes, UUID namespace){
        try {
            return from(bytes, namespace, (byte) 0x50, MessageDigest.getInstance("SHA-1"));
        } catch (NoSuchAlgorithmException e) {
            /** never throw any exception, if throw exception, system is critical state. */
        }
        return UUID.nameUUIDFromBytes(bytes);
    }
}