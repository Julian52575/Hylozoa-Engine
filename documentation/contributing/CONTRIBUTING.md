> [!NOTE] 
> **This document is only valid in the state it is on the latest commit of the `main` branch.**

Hello and thank you for your interest in collaborating with the Hylozoa engine project !  

Here are the steps on getting started:
``` mermaid
flowchart TD
%%%% https://mermaid.ai/app/projects/6c38f33b-3b7d-40c4-ab9d-e647b98da993/diagrams/b0d38ed0-7380-46ee-9834-fd2cf1bfd9ba/share/invite/eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJkb2N1bWVudElEIjoiYjBkMzhlZDAtNzM4MC00NmVlLTk4MzQtZmQyY2YxYmZkOWJhIiwiYWNjZXNzIjoiVmlldyIsImlhdCI6MTc4MjA1MDQyNH0.66Xdllbq8m6803p3JBj2fuI-17RkPoM1ETXczutHwEM?entryPoint=share-modal
%%%% Nodes
Choose("Choose a <b>role</b> from the repo's GOVERNANCE.md"):::yellow
Discord("Join the <b>Discord server</b> !"):::yellow
%%
S("<b>Supporter</b>"):::yellow
S1("<b>Answer community calls</b> from the Discord server !"):::yellow
%%
C("<b>Contributor</b>"):::blue
C1("Read the <b>contributing policies</b>"):::blue
C2("<b>Code in issues or pull requests</b>"):::blue
%%
R("<b>Reviewer</b>"):::pink
R1("Look for <b>open pull requests</b>"):::pink
R2("<b>Comment</b> to stir the contributors in the right direction"):::pink
R3("<b>Mention the owners</b> when a pull request is <b>ready for merge</b>"):::pink
%%%% Edges
Help("<b>I want to contribute to Hylozoa</b>"):::title --> Discord --> Choose
Choose --> C
Choose --> R
Choose --> S
%%
S --> S1
%%
C --> S
C --> C1
C1 --> C2
C2 ~~~ S
%%
R --> C
R --> R1 --> R2 --> R3
R2 ~~~ C
%%%% Styling
classDef title stroke-width:4px,font-size:18;
classDef green fill:#B2DFDB,stroke:#00897B,stroke-width:2px;
classDef orange fill:#FFE0B2,stroke:#FB8C00,stroke-width:2px;
classDef blue fill:#BBDEFB,stroke:#1976D2,stroke-width:2px;
classDef yellow fill:#FFF9C4,stroke:#FBC02D,stroke-width:2px;
classDef pink fill:#F8BBD0,stroke:#C2185B,stroke-width:2px;
classDef purple fill:#E1BEE7,stroke:#8E24AA,stroke-width:2px;
classDef grey fill:#2222,stroke:#110000,stroke-width:2px;
```
