import os, re, glob
from collections import defaultdict

os.makedirs('docs/standalone/audits', exist_ok=True)

call_regex = re.compile(r'plugin::(Call|CallAndReturn|CallMethod|CallMethodAndReturn|CallVirtualMethod|CallVirtualMethodAndReturn)(?:<([^>]+)>)?\s*\(([^;]*)\);')

files = sorted(glob.glob('source/**/*.cpp', recursive=True) + glob.glob('source/**/*.h', recursive=True))

category_calls = defaultdict(list)
total_count = 0

for f in files:
    try:
        with open(f, 'r', errors='ignore') as fp:
            lines = fp.readlines()
            for idx, line in enumerate(lines):
                m = call_regex.search(line)
                if m:
                    total_count += 1
                    call_type = m.group(1)
                    tmpl_args = m.group(2) if m.group(2) else ''
                    
                    addr_match = re.search(r'0x[0-9a-fA-F]+', tmpl_args)
                    addr = addr_match.group(0) if addr_match else 'unknown'
                    
                    cat = 'Miscellaneous'
                    if 'Audio' in f: cat = 'Audio System'
                    elif 'Vehicle' in f or 'Car' in f or 'Bike' in f or 'Plane' in f or 'Train' in f: cat = 'Vehicles & Traffic AI'
                    elif 'Ped' in f or 'Task' in f or 'Decision' in f: cat = 'Pedestrians & Tasks'
                    elif 'Interior' in f or 'Furniture' in f: cat = 'Interiors & Furniture'
                    elif 'Camera' in f or 'Cam' in f: cat = 'Camera Subsystem'
                    elif 'Render' in f or 'Fx' in f or 'Shadow' in f or 'rw' in f: cat = 'Rendering & Special FX'
                    elif 'Script' in f: cat = 'Scripting & SCM'
                    elif 'Memory' in f: cat = 'Memory & Platform'
                    elif 'Hud' in f or 'Font' in f or 'Menu' in f: cat = 'UI & Frontend'
                    elif 'Collision' in f: cat = 'Collision & World Geometry'
                    
                    rel_f = os.path.relpath(f, '.')
                    category_calls[cat].append({
                        'file': rel_f,
                        'line': idx + 1,
                        'type': call_type,
                        'addr': addr,
                        'snippet': line.strip()
                    })
    except Exception as e:
        pass

out_path = 'docs/standalone/audits/PLUGIN_CALL_AUDIT.md'
with open(out_path, 'w') as out:
    out.write('# Audit & Classification: 838 `plugin::Call` Sites\n\n')
    out.write(f'Generated during Phase 4 implementation. Total active `plugin::Call` occurrences: **{total_count}** across **{len(set(c["file"] for cat in category_calls.values() for c in cat))}** files.\n\n')
    out.write('## Summary by Subsystem\n\n')
    out.write('| Subsystem | Call Sites | Default Fallback Strategy |\n')
    out.write('| :--- | :---: | :--- |\n')
    for cat, items in sorted(category_calls.items(), key=lambda x: -len(x[1])):
        strategy = 'Diagnostic stub (`nullptr` / `false` / `0`)'
        if cat == 'Interiors & Furniture':
            strategy = 'Native minimal stubs (`Init`, `AddInterior`, `Exit`, `GetEntity`) + Safe defaults'
        elif cat == 'Memory & Platform':
            strategy = 'Native CRT allocator decoupling (`malloc`/`free`/`realloc`)'
        elif cat == 'Vehicles & Traffic AI':
            strategy = 'Safe traffic AI degradation (bypasses unreversed AI routes)'
        elif cat == 'Camera Subsystem':
            strategy = 'Safe matrix retention; unreversed sequence stubs'
        out.write(f'| {cat} | {len(items)} | {strategy} |\n')
    
    out.write('\n---\n\n')
    out.write('## Detailed Subsystem Breakdown\n\n')
    for cat, items in sorted(category_calls.items(), key=lambda x: -len(x[1])):
        out.write(f'### {cat} ({len(items)} calls)\n\n')
        out.write('| File | Line | Address | Invocation Type |\n')
        out.write('| :--- | :---: | :---: | :--- |\n')
        for item in items[:25]:
            out.write(f'| `{item["file"]}` | {item["line"]} | `{item["addr"]}` | `plugin::{item["type"]}` |\n')
        if len(items) > 25:
            out.write(f'| *(and {len(items) - 25} more call sites)* | ... | ... | ... |\n')
        out.write('\n')

print(f'Wrote {out_path} with {total_count} audited calls.')
