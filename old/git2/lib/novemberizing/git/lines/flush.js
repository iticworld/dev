/**
 *
 * @author novemberizing <novemberizing@gmail.com>
 * @since 0.0.1
 */

import line from '../line';

export default class flush extends line {
    constructor(length){
        super(length, undefined);
        this.type = 'flush';
    }

    static gen(){
        return '0000';
    }
}
