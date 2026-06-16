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
        // Match identifiers before :: (namespace/class like mik::, Assembly::)
        {
          pattern: /\b[a-z_]\w*(?=\s*::)/i,
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

    // Assembly::name() empty parens → yellow (function definition)
    PrismObject.languages.insertBefore('cpp', 'class-name', {
      'assembly-fn': {
        pattern: /(?<=[A-Z]\w*::)\s*[a-z_]\w*(?=\s*\(\s*\))/,
        greedy: true,
      },
    });

    // Assembly::name(args) non-empty parens → blue (variable/constructor)
    PrismObject.languages.insertBefore('cpp', 'assembly-fn', {
      'variable': {
        pattern: /(?<=[A-Z]\w*::)\s*[a-z_]\w*(?=\s*\([^)]*\S[^)]*\))/,
        greedy: true,
      },
    });

    // Control flow keywords → purple
    PrismObject.languages.insertBefore('cpp', 'keyword', {
      'control-keyword': {
        pattern: /\b(?:if|else|for|while|do|switch|case|break|continue|return|goto)\b/,
        greedy: true,
      },
    });

    // Add type names after lowercase namespace :: to class-name (green)
    const existingClassName = PrismObject.languages.cpp['class-name'];
    const namespaceMemberPattern = {
      pattern: /(?<=[a-z_]\w*::)\s*[a-z_]\w*/,
      greedy: true,
    };
    // Known mikLib struct type names (from constants.h) → green
    const mikLibTypesPattern = {
      pattern: /\b(?:drive_constants|heading_constants|turn_constants|swing_constants|turn_to_angle_params|swing_to_angle_params|turn_to_point_params|swing_to_point_params|drive_distance_params|drive_to_point_params|drive_to_pose_params|holonomic_to_pose_params|strafe_distance_params|auto_variation)\b/,
      greedy: true,
    };
    PrismObject.languages.cpp['class-name'] = [
      mikLibTypesPattern,
      namespaceMemberPattern,
      ...(Array.isArray(existingClassName)
        ? existingClassName
        : existingClassName
          ? [existingClassName]
          : []),
    ];

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
