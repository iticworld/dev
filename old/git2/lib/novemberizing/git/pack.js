/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */


import util from "../util";

export default class pack {
    constructor(id, name){
        this.id = id;
        this.name = name;
    }

    want() {
        let options = ['multi_ack_detailed', 'no-done', 'side-band-64k', 'thin-pack', 'ofs-delta', 'deepen-since', 'deepen-not', 'agent=git/2.17.1'];
        let data = 'want ' + this.id + ' ' + options.join(' ') + '\n';
        return util.hex(data.length + 4, '0000') + data;
    }
}
