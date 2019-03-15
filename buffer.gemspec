# frozen_string_literal: true

lib = File.expand_path('lib', __dir__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'buffer/version'

def gem_info(spec)
  spec.name          = 'buffer'
  spec.version       = Buffer::VERSION
  spec.authors       = ['Nikos']
  spec.email         = ['n.mouchtaris@youngcapital.nl']

  spec.summary       = 'java.io.Buffer style for Ruby'
  spec.description   = ''
  spec.homepage      = 'https://github.com/mouchtaris/gems'
  spec.license       = 'MIT'
end

def gem_meta(spec)
  # Prevent pushing this gem to RubyGems.org. To allow pushes either set the
  # 'allowed_push_host' to allow pushing to a single host or delete this
  # section to allow pushing to any host.
  if spec.respond_to?(:metadata)
    spec.metadata['allowed_push_host'] = "TODO: Set to 'http://mygemserver.com'"

    spec.metadata['homepage_uri'] = spec.homepage
    spec.metadata['source_code_uri'] = 'https://github.com/mouchtaris/gems'
    spec.metadata['changelog_uri'] = 'https://github.com/mouchtaris/gems/blob/buffer/master/CHANGELOG.md'
  else
    raise 'RubyGems 2.0 or newer is required to protect against ' \
      'public gem pushes.'
  end
end

def gem_files(spec)
  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been
  # added into git.
  spec.files = Dir.chdir(File.expand_path(__dir__)) do
    `git ls-files -z`
      .split("\x0")
      .reject { |f| f.match(%r{^(test|spec|features)/}) }
  end
  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
end

def gem_deps(spec)
  spec.add_development_dependency 'bundler', '~> 2.0'
  spec.add_development_dependency 'rake', '~> 10.0'
  spec.add_development_dependency 'rspec', '~> 3.0'
end

Gem::Specification.new do |spec|
  gem_info spec
  gem_meta spec
  gem_files spec
  gem_deps spec
end
