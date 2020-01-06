import novemberizing from './lib/novemberizing';

let example = new novemberizing.git.repository('http://gitlab.example.com/novemberizing/example.git', 'novemberizing', 'novemberizing');

async function clone(){

}
example.clone();

// novemberizing.git.clone('http://gitlab.example.com/novemberizing/example.git', 'novemberizing', 'novemberizing');
// novemberizing.git.upload.pack('http://gitlab.example.com/novemberizing/example.git', 'novemberizing', 'novemberizing');



// import { git } from './lib/git';
//
// git.clone('http://gitlab.example.com/novemberizing/example.git', 'novemberizing', 'novemberizing');

// let git = new git('http://gitlab.example.com/novemberizing/example.git', 'novemberizing', 'novemberizing');
//
// git.clone();

// 001e# service=git-upload-pack\n //
