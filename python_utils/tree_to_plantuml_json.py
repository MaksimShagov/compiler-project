import json
from argparse import ArgumentParser

def parse_args():
    parser = ArgumentParser(
        prog='ProgramName',
        description='What the program does',
        epilog='Text at the bottom of help'
    )

    parser.add_argument(
        '-f', '--file-path', type=str, required=True,
        help="Path to text file with tree view"
    )

    return parser.parse_args()

def get_childrens(nested_list, index, nested_level):
    # print(nested_list)
    
    children = []
    for idx in range(index+1, len(nested_list)):
        if nested_list[idx][0] - nested_level == 1:
            children.append(
                {
                    nested_list[idx][1]:
                    get_childrens(nested_list, idx, nested_list[idx][0])
                }
            )
        elif nested_list[idx][0] - nested_level == 0:
            for child in children:
                if len(list(child.values())[0]) == 0:
                    name, value = list(child.keys())[0].split(': ')
                    child[name] = value
                    child.pop(list(child.keys())[0])
            return children
    for child in children:
        if len(list(child.values())[0]) == 0:
            if list(child.keys())[0].find(':') != -1:
                name, value = list(child.keys())[0].split(': ')
                child[name] = value
                child.pop(list(child.keys())[0])
    return children

def main():

    args = parse_args()
    src = args.file_path

    with open(src, 'r') as file:
        tree_str = file.read()

    tree_list = tree_str.split('\n')
    nested_view = []

    for element in tree_list:
        nested_view.append(((element.rfind('  ') + 2) // 2, element.replace('  ', '')))

    lists = get_childrens(nested_view, 0, 0)

    json_tree = json.dumps(lists, indent=2)
    with open("tree.json", 'w') as file:
        file.write(json_tree)

main()

