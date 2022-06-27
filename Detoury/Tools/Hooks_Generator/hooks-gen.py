# Imports
import re
import os
import jinja2 as jinja

#
# Functions
#

# Get current script dir path
def get_script_dir():
    return os.path.dirname(os.path.realpath(__file__))

# Returns a list of file absolute paths inside a directory
def listdir_iterator(path):
    for filename in os.listdir(path):
        yield(path + "/" + filename)

# Parse MSDB Hook API style file and return a dictionary of all info about the API
def parse_api_hook_file(filepath) :
    with open(filepath, "r+") as f:
        # Prepare the lines of the file
        lines = f.readlines()
        # Search for the API name and return type (first line)
        match__apiname_and_return = re.match(r".*?(\w+)\s+(\w+)\s*\(.*", lines[0], flags=re.MULTILINE)
        return_type = match__apiname_and_return.group(1)
        api_name    = match__apiname_and_return.group(2)
        # Get the parameters
        api_params_list = []
        for line in lines[1:]:
            match__param_token_and_param_type = re.match(r"^[^\]]+\]\s+(\w+)\s+(\w+),?", line, flags=re.MULTILINE)
            # Skip the last line to avoid accessing None object
            if (match__param_token_and_param_type == None):
                continue
            param_type = match__param_token_and_param_type.group(1)
            param_name = match__param_token_and_param_type.group(2)
            api_params_list.append({ "param_type" : param_type, "param_name" : param_name})
        
        return ( {"api_name" : api_name, "return_type" : return_type, "params" : api_params_list} )

def render_template(template_dir_path, template_filename, hooks_data):
    template_loader = jinja.FileSystemLoader(searchpath = template_dir_path)
    template_env    = jinja.Environment(loader = template_loader)
    template_file   = template_filename
    template        = template_env.get_template(template_file)
    output          = template.render(hooks_data = hooks_data)
    return (output)

#
# Main
#
def main():
    hooks_data = []
    # Parsing stage
    # 1. Get script path
    path = get_script_dir()
    hooks_path = path + "/Hooks"
    # 2. Iterate over every single file to fetch and append data to hooks_data
    for api_file_path in listdir_iterator(hooks_path):
        # Parse each file and readlines
        api_info = parse_api_hook_file(api_file_path)
        # Add all info of API in single dictionary
        hooks_data.append(api_info)
    # Generation stage
    template_dir_path = path + "/Template"
    template_filename = "hooks_template.cpp"
    hooks_data = { "name": "Islam NEGM" }
    output = render_template(template_dir_path, template_filename, hooks_data)
    print(output)
    
if __name__ == "__main__":
    main()

