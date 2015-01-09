Contributing
============

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

Compatibility
-------------

The node addons API has gone through some major changes over the years.
This module has a few implementations in the `src/` directory for
different node module API versions. If you change one implementation,
the change may need to be applied to the other implementations.

Try not to decrease the list of supported platforms / node versions.

Testing
-------

Use a tool such as [nvm](https://github.com/creationix/nvm) to install
the versions of node.js listed in the matrix below. On each of them,
do a fresh `npm install && npm test` of this module. Everything should
work.

| Series  | Minimum Version | Maximum Version |
| ------- | --------------- | --------------- |
| v0.10.x |        v0.10.16 |    latest v0.10 |
| v0.11.x |        v0.11.13 |    latest v0.11 |

These versions are also listed in `README.md` and `package.json`. If
they change, update them there too. For the most part, your changes
should not impact versions that are already supported.