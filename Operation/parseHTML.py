import re


def parseHTML():
    with open('../output.html', 'r') as f:
        html = f.read()

        # Extract headers
        headers = {}
        header_pattern = re.compile(r'^(Subject|From|To): (.+)$', re.MULTILINE)
        for match in header_pattern.finditer(html):
            headers[match.group(1)] = match.group(
                2).replace('<', '&lt;').replace('>', '&gt;')

        # Extract content starting from <!DOCTYPE>
        doctype_index = html.find('<!DOCTYPE')
        if doctype_index != -1:
            html_content = html[doctype_index:]
        else:
            html_content = ""

        # Prepare the content to be written back
        output_content = ""
        for header, value in headers.items():
            output_content += f"<p>{header}: {value}<br></p>"
        output_content += html_content

        # Decode the quoted printable
        output_content = output_content.replace('=\n', '')
        output_content = output_content.replace('=20', ' ')
        output_content = output_content.replace('=3D', '=')
        output_content = output_content.replace('=C2=A0', ' ')
        output_content = output_content.replace('=E2=80=93', '-')
        output_content = output_content.replace('=E2=80=94', '-')
        output_content = output_content.replace('=E2=80=98', "'")
        output_content = output_content.replace('=E2=80=99', "'")
        output_content = output_content.replace('=E2=80=9C', '"')
        output_content = output_content.replace('=E2=80=9D', '"')
        output_content = output_content.replace('=E2=80=A6', '...')
        output_content = output_content.replace('=E2=80=A8', ' ')
        output_content = output_content.replace('=E2=80=A9', ' ')

        # remove the last two lines
        output_content = output_content.split('\n')
        output_content = output_content[:-2]
        output_content = '\n'.join(output_content)

        print(output_content)
        with open('../output.html', 'w') as f:
            f.write(output_content)
        return


if __name__ == '__main__':
    parseHTML()
