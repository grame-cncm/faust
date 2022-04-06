// const path = require('path');

// module.exports = {
//   entry: './npm/node/node.js',
//   output: {
//     path: path.resolve(__dirname, 'npm'),
//     filename: 'FaustNode.js',
//   },
//   mode: 'production',    
// };


const path = require('path');

module.exports = {
  entry: [
    './node/libfaust.js', 
    './node/FaustCompiler.js', 
    './node/FaustGenerator.js', 
    './node/FaustUtilities.js', 
    './node/index.js'
  ],
  output: {
    filename: 'FaustNode.js',
    path: path.resolve(__dirname, './npm'),
    library: {
      type: 'commonjs2',
    },
  },
  mode: 'production', 
};