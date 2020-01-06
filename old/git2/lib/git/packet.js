/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

/**
 *
 */
export class packet {
    static parse(s){
        let start = 0;
        let length = 0;
        let lines = [];
        /**
         *
         * @todo Clients must validate the first five bytes of the response entity matches the regex '_^\[0-9a-f\]{4}#_'. If this test fails, client must not continue.
         */
        while(start < s.length) {
            length = parseInt('0x' + s.slice(start, start + 4));
            if(length !== 0) {
                lines.push(new packet(length, s.slice(start + 4, start + length)));
                start += length;
            } else {
                lines.push(new packet(length, undefined));
                start += 4;
            }
        }
        return lines;
    }

    /**
     * parse packet data
     *
     * @param s {string} packet value
     * @private
     */
    __parse(s) {
        if(s[0] === '#') {
            /**
             * check service=
             */
            console.log(s.indexOf('service'));
        }
    }

    /**
     *
     * @param length {number} packet length
     * @param data {string} data
     */
    constructor(length, data){
        this.length = length;
        this.type = undefined;
        if(this.length !== 0){
            this.__parse(this.data = data);
        } else {
            this.data = undefined;
        }
    }
}