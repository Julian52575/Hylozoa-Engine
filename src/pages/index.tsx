import type {ReactNode} from 'react';
import clsx from 'clsx';
import Link from '@docusaurus/Link';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import Layout from '@theme/Layout';
import HomepageFeatures from '@site/src/components/HomepageFeatures';
import Heading from '@theme/Heading';

import styles from './index.module.css';

function HomepageHeader() {
  return (
    <header className={clsx('hero hero--primary', styles.heroBanner)}>
      <div className="container">

        {/* PROJECT NAME */}
        <Heading as="h1" className="hero__title">
          Hylozoa Engine
        </Heading>

        {/* TAGLINE */}
        <p className="hero__subtitle">
          Open-source C++ Game Engine.
          <b> Make complex ecosystems, not complex code. </b>
        </p>

        {/* GET STARTED BUTTON */}
        <div className={styles.buttons} style={{ display: "flex", flexDirection: "column", gap: "1rem", fontWeight: 400 }}>
          <Link className="button button--secondary button--lg" to="/tutorials/intro"
            style={{ padding: "0.75rem 1.5rem", fontWeight: 400 }}
          >
            <b>Yes !</b> I am tired of difficult engines, <b> show me Hylozoa ! </b>
          </Link>

          <Link className="button button--secondary button--lg" to="/tutorials/intro"
            style={{ padding: "0.75rem 1.5rem", fontWeight: 400 }}
          >
            <b>Yes !</b> I love complete ecosystems, <b> show me Hylozoa ! </b>
          </Link>
        </div>
      </div>
    </header>
  );
}

function TeamSection() {
  const team = [
    {
      name: "Sacha DACALOR-FOURCADE",
      role: "Imaginer / Architect / Lead Developer",
      emoji: "🌌",
      image: "https://media.licdn.com/dms/image/v2/D4E03AQEchlNmbfPB5w/profile-displayphoto-shrink_800_800/profile-displayphoto-shrink_800_800/0/1726479467960?e=1779321600&v=beta&t=Pziw8OIGHYa9SjH6k2BU1kI67TYvj_fOpqezua2-zTk",
      link: "https://github.com/Sachet2Plastik",
    },
    {
      name: "Julian Bottiglione",
      role: "Team Assistant / DevOps / Quality Assurance / Tools maker / Debugger",
      emoji: "🏗️",
      image: "https://media.licdn.com/dms/image/v2/D4E03AQGOKDNbrXLhyA/profile-displayphoto-shrink_800_800/B4EZXYqplNGwAo-/0/1743096814621?e=1779321600&v=beta&t=zHqa79a3l_haBO5vHHbTLE-4qBXq8elmPXr5wnU-ZWE",
      link: "https://github.com/Julian52575",
    },
    {
      name: "Antoine Weisse",
      role: "Miracle Maker / UI / Anything we need",
      emoji: "💪🏃",
      image: "https://media.licdn.com/dms/image/v2/D4E03AQFK2UVxhfLzog/profile-displayphoto-shrink_800_800/B4EZUYNZOwH0Ag-/0/1739867919818?e=1779321600&v=beta&t=DQMwl4yGEqkLY6zA4o3YfArYvN_c2mHONnwj2rKC7oc",
      link: "https://github.com/Antoineweisse",
    },
    {
      name: "Raphael Vaz",
      role: "Thinking / Documents",
      emoji: "🧠",
      image: "https://avatars.githubusercontent.com/u/114603350?v=4",
      link: "https://github.com/Raphael-v",
    },
    {
      name: "YOU",
      role: "Contributor",
      emoji: "🫵",
      image: "https://upload.wikimedia.org/wikipedia/commons/c/c2/GitHub_Invertocat_Logo.svg",
      link: "contributing/intro",
    }
  ];

  return (
    <section className="padding-vert--xl">
        <div className="container"> <Heading as="h1" style={{ textAlign: "center" }}>
          👥 The Team </Heading>
          <p style={{ textAlign: "center", marginBottom: "3rem", fontSize: "1.2rem" }}>
            Meet the 5 puzzle pieces that make up the Hylozoa Team! <br/>
          </p>
        </div>
        <div className="row">
    {team.map((member, i) => (
      <div className="col col--4 margin-bottom--lg" key={i}>
        <a
          href={member.link}
          target="_blank"
          rel="noopener noreferrer"
          style={{ textDecoration: "none", height: "100%", display: "block" }}
        >
          <div
            style={{
              textAlign: "center",
              padding: "2rem",
              borderRadius: "16px",
              border: "1px solid var(--ifm-color-emphasis-200)",
              background: "var(--ifm-background-surface-color)",
              height: "100%",                 // ✅ same height
              display: "flex",                // ✅ flex layout
              flexDirection: "column",
              justifyContent: "space-between",// ✅ spread content
              alignItems: "center",
            }}
          >
            {/* IMAGE */}
            <img
              src={member.image}
              alt={member.name}
              style={{
                width: "96px",
                height: "96px",
                borderRadius: "50%",
                objectFit: "cover",
                marginBottom: "1rem",
                border: "2px solid var(--ifm-color-primary)",
              }}
            />

            {/* TEXT BLOCK */}
            <div>
              <h3 style={{ marginBottom: "0.5rem" }}>{member.name}</h3>
              <p style={{ opacity: 0.7, minHeight: "48px" }}>
                {member.role}
              </p>
            </div>

            {/* EMOJI */}
            <p style={{ fontSize: "1.5rem", marginTop: "1rem" }}>
              {member.emoji}
            </p>
          </div>
        </a>
      </div>
    ))}
</div>
    </section>
  );
}

function ProjectSection() {
  return (
    <section className="padding-vert--xl">
      <div className="container">
        <Heading as="h1" style={{ textAlign: "center" }}>
          🐜🪸🌲 About the Engine
        </Heading>

        <p style={{ textAlign: "center", maxWidth: 700, margin: "0 auto 3rem", fontSize: "1.2rem" }}>
          <p style={{ textAlign: "center", maxWidth: 700, fontSize: "1.0rem", marginBottom: "1.5rem" }}> 
            <i>Have you ever tought of how complex it would be to program an ant colony, a coral reef or a rainforest ?</i><br/>
          </p>
          
          Lucky for you, we have too !<br/>
          You now live in a world where you can create these ecosystems <b>without wrestling with the engine itself</b>.
        </p>

        <div className="row">
          {[
            { title: "⚡ Real-time Rendering", desc: "High-performance rendering pipeline using the new SDL3." },
            { title: "🧩 Modular Architecture", desc: "Clean, extensible systems built for handling complex entities." },
            { title: "🛠️ Easy to get started", desc: "Dev environment and tools built for ease of use." },
            { title: "💂 Performance-first", desc: "Optimized execution thanks to our strict testing and benchmarking." },
            { title: "🖥️ Multi-OS", desc: "Support for Windows and Linux." },
            { title: "🚀 Open-Source", desc: "Fully open-source and community-driven." },
          ].map((item, i) => (
            <div className="col col--4 margin-bottom--lg" key={i}>
              <div style={{
                padding: "1.5rem",
                borderRadius: "12px",
                border: "1px solid var(--ifm-color-emphasis-200)",
                height: "100%",
                background: "var(--ifm-background-surface-color)"
              }}>
                <h3>{item.title}</h3>
                <p>{item.desc}</p>
              </div>
            </div>
          ))}
        </div>
      </div>
    </section>
  );
}

export default function Home(): ReactNode {
  return (
    <Layout
      title="Hylozoa Engine"
      description="Open-source C++ Game Engine">

      <HomepageHeader />

      <main>
        <ProjectSection />
        <TeamSection />
      </main>

    </Layout>
  );
}