import type {PrismLib} from 'prism-react-renderer';
import defaultInclude from '@docusaurus/theme-classic/lib/theme/prism-include-languages';

export default function prismIncludeLanguages(PrismObject: PrismLib): void {
  defaultInclude(PrismObject);

  // Extend C++ grammar to recognize mik:: namespace patterns
  const cpp = PrismObject.languages.cpp;
  if (cpp) {
    PrismObject.languages.insertBefore('cpp', 'function', {
      'class-name': [
        // Match capitalized type names in declarations (e.g., Chassis in "Chassis chassis(")
        {
          pattern: /\b[A-Z]\w*(?=\s+[a-z_]\w*)/,
          greedy: true,
        },
        // Match identifiers before :: (namespace/class usage like mik::motor)
        {
          pattern: /\b[a-z_]\w*(?=\s*::)/i,
          greedy: true,
        },
        // Match identifiers after :: (class/function like motor, motor_group)
        {
          pattern: /(?<=::)\s*[a-z_]\w*/i,
          greedy: true,
        },
        // Keep existing class-name patterns
        ...(Array.isArray(cpp['class-name'])
          ? cpp['class-name']
          : cpp['class-name']
            ? [cpp['class-name']]
            : []),
      ],
    });

    // Add bracket tokens — VSCode bracket pair colorizer style
    PrismObject.languages.insertBefore('cpp', 'operator', {
      // ( immediately before { → purple
      'paren-brace': {
        pattern: /\((?=\{)/,
      },
      // ) immediately after } → purple
      'paren-after-brace': {
        pattern: /(?<=\})\)/,
      },
      // { } → blue
      'brace': {
        pattern: /[{}]/,
      },
      // regular ( ) [ ] → yellow
      'bracket': {
        pattern: /[()[\]]/,
      },
    });
  }
}
