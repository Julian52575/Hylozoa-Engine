import {themes as prismThemes} from 'prism-react-renderer';
import type {Config} from '@docusaurus/types';
import type * as Preset from '@docusaurus/preset-classic';

// This runs in Node.js - Don't use client-side code here (browser APIs, JSX...)

const config: Config = {
  title: 'Hylozoa Engine',
  tagline: 'From the ashes of the old world, a new engine rises.',
  favicon: 'img/favicon.ico',

  // Future flags, see https://docusaurus.io/docs/api/docusaurus-config#future
  future: {
    v4: true, // Improve compatibility with the upcoming Docusaurus v4
  },

  // Set the production url of your site here
  url: 'https://julian52575.github.io',
  // Set the /<baseUrl>/ pathname under which your site is served
  // For GitHub pages deployment, it is often '/<projectName>/'
  baseUrl: '/Hylozoa-Engine/',

  // GitHub pages deployment config.
  // If you aren't using GitHub pages, you don't need these.
  organizationName: 'julian52575', // Usually your GitHub org/user name.
  projectName: 'Hylozoa-Engine', // Usually your repo name.

  onBrokenLinks: 'ignore',

  // Even if you don't use internationalization, you can use this field to set
  // useful metadata like html lang. For example, if your site is Chinese, you
  // may want to replace "en" with "zh-Hans".
  i18n: {
    defaultLocale: 'en',
    locales: ['en'],
  },

  presets: [
    [
      '@docusaurus/preset-classic',
      {
        docs: {
          sidebarPath: './sidebars.ts',
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            'https://github.com/Julian52575/Hylozoa-Engine.git',
        },
        blog: {
          showReadingTime: true,
          feedOptions: {
            type: ['rss', 'atom'],
            xslt: true,
          },
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            'https://github.com/Julian52575/Hylozoa-Engine.git',
          // Useful options to enforce blogging best practices
          onInlineTags: 'warn',
          onInlineAuthors: 'warn',
          onUntruncatedBlogPosts: 'warn',
        },
        theme: {
          customCss: './src/css/custom.css',
        },
      } satisfies Preset.Options,
    ],
  ],

  themeConfig: {
    // Replace with your project's social card
    image: 'img/docusaurus-social-card.jpg',
    colorMode: {
      respectPrefersColorScheme: true,
    },
    navbar: {
      title: 'Hylozoa Engine',
      logo: {
        alt: 'Hylozoa Engine Logo',
        src: 'img/logo.svg',
      },
      items: [
        /*
        {
          to: '/docs/intro',
          label: 'Docs',
          position: 'left',
        },
        {
          to: '/tutorials/intro',
          label: 'Tutorials',
          position: 'left'
        },
        {
          to: '/contributing/intro',
          label: 'Contributing',
          position: 'left'
        },
        */
        {
          to: '/blog',
          label: 'Blog',
          position: 'left'
        },
        {
          href: 'https://github.com/Julian52575/Hylozoa-Engine',
          label: 'GitHub',
          position: 'right',
        },
      ],
    },
    footer: {
      style: 'dark',
      links: [
        {
          title: 'Ressources',
          items: [
            /*{
              label: 'Docs',
              to: '/docs/intro',
            },
            {
              label: 'Contributing',
              to: '/contributing',
            },
            */
          ],
        },
        {
          title: 'Community',
          items: [
            {
              label: 'Stack Overflow',
              href: 'https://stackoverflow.com/questions/tagged/docusaurus',
            },
            {
              label: 'Discord',
              href: 'https://discordapp.com/invite/docusaurus',
            },
            {
              label: 'X',
              href: 'https://x.com/docusaurus',
            },
          ],
        },
        {
          title: 'More',
          items: [
            {
              label: 'GitHub',
              href: 'https://github.com/Julian52575/Hylozoa-Engine',
            },
          ],
        },
      ],
      copyright: `Copyright © ${new Date().getFullYear()} Hylozoa Engine, Inc. Built with Docusaurus.`,
    },
    prism: {
      theme: prismThemes.github,
      darkTheme: prismThemes.dracula,
    },
  } satisfies Preset.ThemeConfig,

  /*
  plugins: [
    [
      '@docusaurus/plugin-content-docs',
      {
        id: 'tutorials',                // 👈 important, unique ID
        path: 'tutorials',     // 👈 your folder
        routeBasePath: 'tutorials',     // 👈 URL: /tutorials/...
        sidebarPath: require.resolve('./sidebarsExtra.js'),
      },
    ],
  ],
  */
};

export default config;
