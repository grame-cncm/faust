# Testing JOSS Paper Compilation

## Steps to Test Paper Compilation on GitHub

1. **Go to your GitHub repository**: `https://github.com/grame-cncm/faust`

2. **Navigate to Actions tab** in the repository

3. **Create new workflow file**:
   - Click "New workflow" or "set up a workflow yourself"
   - Name the file: `.github/workflows/draft-pdf.yml`

4. **Copy this exact workflow content**:
```yaml
on: [push, pull_request]

jobs:
  paper:
    runs-on: ubuntu-latest
    name: Paper Draft
    steps:
      - name: Checkout
        uses: actions/checkout@v3
      - name: Build draft PDF
        uses: openjournals/openjournals-draft-action@master
        with:
          journal: joss
          paper-path: paper.md
      - name: Upload
        uses: actions/upload-artifact@v3
        with:
          name: paper
          path: paper.pdf
```

5. **Commit the workflow file**

6. **Check if it runs**:
   - Go back to Actions tab
   - Should see "Paper Draft" workflow running
   - Wait for it to complete (green checkmark = success)

7. **Download the PDF**:
   - Click on the successful workflow run
   - Download the "paper" artifact
   - Check the generated PDF looks correct

## Expected Result
- Workflow should complete successfully
- Generated PDF should match your paper.md content
- No compilation errors

## If It Fails
- Check the error logs in the Actions tab
- Common issues: missing bibliography file, malformed YAML header, citation errors