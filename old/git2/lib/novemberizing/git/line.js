/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import util from "../util";

export default class line {
    /**
     * constructor
     *
     * @param length {Number} line length
     * @param data {String} line data
     */
    constructor(length, data){
        this.length = length;
        this.data = data;
        this.type = 'line';
    }

    static gen(data){
        console.log("===================");
        console.log(util.hex(data.length + 4, '0000'));
        return util.hex(data.length + 4, '0000') + data ;
    }
}
