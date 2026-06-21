> [!NOTE] 
> **This document is only valid in the state it is on the latest commit of the `main` branch.**

Hello and thank you for your interest in collaborating with the Hylozoa engine project !  

Here are the steps on getting started:

``` mermaid
flowchart LR
    Help("<b>I want to contribute to Hylozoa</b>") --> Discord("Join the <b>Discord server</b> !")
    Discord --> Choose@{ label: "Choose a <b>role</b> from the repo's GOVERNANCE.md" }
    Choose --> C("<b>Contributor</b>") & R("<b>Reviewer</b>") & S("<b>Supporter</b>")
    S --> S1("<b>Answer community calls</b> from the Discord server !")
    C --> S & C1("Read the <b>contributing policies</b>")
    C1 --> C2("<b>Code in issues or pull requests</b>")
    C2 ~~~ S
    R --> C & R1("Look for <b>open pull requests</b>")
    R1 --> R2("<b>Comment</b> to stir the contributors in the right direction")
    R2 --> R3("<b>Mention the owners</b> when a pull request is <b>ready for merge</b>")
    R2 ~~~ C
    Choose@{ shape: rounded}
     Choose:::yellow
     Discord:::yellow
     S:::yellow
     S1:::yellow
     C:::blue
     C1:::blue
     C2:::blue
     R:::pink
     R1:::pink
     R2:::pink
     R3:::pink
     Help:::title
    classDef title stroke-width:4px,font-size:18
    classDef green fill:#B2DFDB,stroke:#00897B,stroke-width:2px
    classDef orange fill:#FFE0B2,stroke:#FB8C00,stroke-width:2px
    classDef blue fill:#BBDEFB,stroke:#1976D2,stroke-width:2px
    classDef yellow fill:#FFF9C4,stroke:#FBC02D,stroke-width:2px
    classDef pink fill:#F8BBD0,stroke:#C2185B,stroke-width:2px
    classDef purple fill:#E1BEE7,stroke:#8E24AA,stroke-width:2px
    classDef grey fill:#2222,stroke:#110000,stroke-width:2px
```


