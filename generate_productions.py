#!/usr/bin/env python3
"""
Code generator: Parse Productions.def and generate Productions.h with aggregated alternatives
"""

import re
from collections import defaultdict

def parse_productions_def(filepath):
    """Parse Productions.def and return a dict of {symbol: [alternatives]}"""
    productions = defaultdict(list)
    
    with open(filepath, 'r') as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('//'):
                continue
            
            # Match: PROD(name, arg1, arg2, ...)
            match = re.match(r'PROD\((\w+)\s*(?:,\s*(.+?))?\s*\)', line)
            if match:
                symbol = match.group(1)
                args_str = match.group(2) if match.group(2) else ""
                
                # Split arguments by comma, handling nested tokens
                if args_str.strip():
                    args = [arg.strip() for arg in args_str.split(',')]
                else:
                    args = []
                
                productions[symbol].append(args)
    
    return productions

def generate_productions_h(productions):
    """Generate C++ code for Productions.h"""
    
    output = []
    output.append("#ifndef PRODUCTIONS_H")
    output.append("#define PRODUCTIONS_H")
    output.append("")
    output.append("#include \"Symbols.h\"")
    output.append("#include <tuple>")
    output.append("")
    output.append("// Productions template specializations")
    output.append("template<typename T>")
    output.append("struct Productions;")
    output.append("")
    output.append("using namespace Symbols;")
    output.append("")
    
    # Generate template specializations grouped by symbol
    for symbol in sorted(productions.keys()):
        alternatives = productions[symbol]
        output.append(f"template<>")
        output.append(f"struct Productions<{symbol}> {{")
        output.append(f"    using alternatives = std::tuple<")
        
        # Generate each alternative tuple
        alt_lines = []
        for args in alternatives:
            if args:
                arg_str = ", ".join(args)
                alt_lines.append(f"        std::tuple<{arg_str}>")
            else:
                alt_lines.append(f"        std::tuple<>")
        
        output.append(",\n".join(alt_lines))
        output.append("    >;")
        output.append("};")
        output.append("")
    
    output.append("#endif")
    return "\n".join(output)

if __name__ == "__main__":
    import sys
    
    input_file = "ParserDir/Productions.def"
    output_file = "header/Productions.h"
    
    # Parse the input file
    productions = parse_productions_def(input_file)
    
    # Generate and write output
    code = generate_productions_h(productions)
    
    with open(output_file, 'w') as f:
        f.write(code)
    
    print(f"Generated {output_file} with {len(productions)} non-terminals")
    for symbol in sorted(productions.keys()):
        print(f"  {symbol}: {len(productions[symbol])} alternative(s)")
