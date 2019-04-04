# frozen_string_literal: true

lib = File.expand_path('lib', __dir__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'ruby_gem'

# Don't freak
public

def spec
  self
end

def gem_data!
  spec.name          = RubyGem::NAME
  spec.version       = RubyGem::VERSION
  spec.authors       = RubyGem::AUTHORS
  spec.email         = RubyGem::EMAIL

  spec.summary       = RubyGem::SUMMARY
  spec.description   = RubyGem::DESCRIPTION
  spec.homepage      = RubyGem::HOMEPAGE
  spec.license       = RubyGem::LICENCE
end

def gem_metadata!
  if spec.respond_to?(:metadata)
    spec.metadata['allowed_push_host'] = RubyGem::ALLOWED_PUSH_HOST

    spec.metadata['homepage_uri'] = spec.homepage
    spec.metadata['source_code_uri'] = RubyGem::SOURCE_CODE_URI
    spec.metadata['changelog_uri'] = RubyGem::CHANGELOG_URI
  else
    raise 'RubyGems 2.0 or newer is required to protect against ' \
      'public gem pushes.'
  end
end

def gem_files!
  spec.files = Dir.chdir(File.expand_path(__dir__)) do
    `git ls-files -z`
      .split("\x0")
      .reject { |f| f.match(%r{^(test|spec|features)/}) }
  end
  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
end

def gem_dependencies!
  spec.add_development_dependency 'bundler', '~> 2.0'
  spec.add_development_dependency 'rake', '~> 10.0'
  spec.add_development_dependency 'rspec', '~> 3.0'
end

Gem::Specification.new do |spec|
  spec.gem_data!
  spec.gem_metadata!
  spec.gem_files!
  spec.gem_dependencies!
end
